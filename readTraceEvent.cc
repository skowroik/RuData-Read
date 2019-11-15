#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <valarray>
#include <string.h>
#include <TFile.h>
#include <TTree.h>
#include <TSpline.h>

#include "TraceEvent.h"

using namespace std;

const uint16_t inpMagicMask   = 0xFFF0;       // in AGATA the low nibble identifies the mezzanine
const uint16_t inpMagicData   = 0xDA00;
const uint16_t inpMagicWave   = 0xDA50;
const uint16_t inpMagicSpec   = 0xDA60;
const uint16_t inpIdleMask    = 0x0008;
const uint16_t inpPileMask    = 0x0001;

struct ggpDomHeader {

  uint16_t key = 0;
  uint16_t evn_0 = 0;
  uint16_t evn_1 = 0;
  uint16_t ts_0 = 0;
  uint16_t ts_1 = 0;
  uint16_t ts_2 = 0;
  uint16_t num_samples = 0;
  uint16_t total_length = 0;
  uint16_t crystal_id = 0;
  uint16_t status = 0;          // bit_0=Pile-up; bit_1=0 bit_2=0; bit_3=Idle-bit; bit_4...bit_15=0
  uint16_t spare[6] = { 0 };

  uint32_t GetEvnum()   const { return ( uint32_t(evn_1) << 16 ) | ( uint32_t( evn_0 ) ); }
  uint64_t GetTstamp()  const { return ( uint64_t( ts_2 ) << 32) | ( uint64_t( ts_1 ) << 16) | ( uint64_t( ts_0 ) ); }
  uint16_t GetStatus()  const { return ( status & 0xF ); }  // keep only the 4 defined bits
  uint16_t GetNumSamp() const { return num_samples; }
  uint16_t GetCrystal() const { return crystal_id; }
  bool     IsData()     const { return (key&inpMagicMask) == inpMagicData; }
  bool     IsWave()     const { return (key&inpMagicMask) == inpMagicWave; }
  bool     IsSpec()     const { return (key&inpMagicMask) == inpMagicSpec; }
  bool     IsIdle()     const { return ((status&inpIdleMask) != 0); }
  bool     IsPileUp()   const { return ((status&inpPileMask) != 0); }
  
};

struct ggpSubHeader {

  uint16_t key = 0;
  uint16_t ener_0 = 0;
  uint16_t ener_1 = 0;
  uint16_t status = 0;
  uint16_t spare_0 = 0;
  uint16_t spare_1 = 0;
  uint16_t compr_type = 0;
  uint16_t compr_len = 0;

  int  GetEnergy() const { return uint32_t( ener_1 ) << 16 | uint32_t( ener_0 ); }
  //ggpSubHeader() { memset(this, 0, sizeof(ggpSubHeader)); }
  
};

void CFD_filter( float* trace, float* CFD_trace, float &CFD_zero, float &baseline, double &riseTime );

void interpolation( float* trace, double &derivMax, double &riseTime, float &baseline, float &maxSig );

void readTraceEvent( char* inFile, ULong64_t nEvents );

void loopData( char* in, ULong64_t nEvents ){
  
  const char* ext = ".i1";
  const char* inDir = in;

  char* dir = gSystem->ExpandPathName( inDir );
  void* dirp = gSystem->OpenDirectory( dir );

  const char* entry;
  const char* filename[ 100 ];
  Int_t l = 0;
  TString str;

  while( ( entry = (char*)gSystem->GetDirEntry( dirp ) ) ){
    str = entry;
    if( str.EndsWith(ext) )
      filename[ l++ ] = gSystem->ConcatFileName( dir, entry );
  }

  for (Int_t a = 0; a < l; ++a) readTraceEvent( (char*)filename[ a ], nEvents );
  
}

void readTraceEvent( char* inFile, ULong64_t nEvents ){

  string file1( inFile );
  string file2 = file1.substr( 0 , file1.size( ) - 3 );
  string file = file2 + ".root";
  ifstream inputFile;
  inputFile.open( inFile , std::ios::binary );                // opening the file
  if( !inputFile.is_open() ){
    
    cerr << "Input File not open please check the file name: " << inFile << endl;
    return;
    
  }

  unsigned long long timeStamp;             // variables of interest for the analysis
  float traceEnergy;
  float energy;
  unsigned short samples[100] ;
  float ftrace [100];
  float baseline;
  unsigned short channel;
  double derivMax = 0;
  double riseTime;
  float CFD [100];
  float CFDzero;
  
  const int SIZE_CHAN = 36;                                                         // variables to divide binary data
  const int SIZE_HEAD = sizeof( ggpDomHeader );
  const int SIZE_SHEAD = sizeof( ggpSubHeader );
  const int SIZE_TRACE = 100 * sizeof( uint16_t );

  int EV_SIZE = SIZE_HEAD + ( SIZE_SHEAD + SIZE_TRACE )*( SIZE_CHAN );;                // Event size


  TraceEvent event;
  TFile *fileOut =  new TFile( file.c_str( ),"recreate" );                       // to write on root file
  TTree *theTree = new TTree( "ggpData","ggpData" );
  unsigned short *theBuffer;
  theTree->Branch( "TraceEvent", &event ); 
  
  ggpDomHeader *theEvent_header = new ggpDomHeader;                                 // structs pointers
  ggpSubHeader *theChannel_header = new ggpSubHeader;                                                       
  char bin [ EV_SIZE ];

  int evCount = 0;
  
  while( inputFile.read( bin , sizeof( bin ) ) ){

    if( nEvents > 0 && evCount > nEvents) break;

    theBuffer = ( unsigned short* )bin;

    memcpy( (char*)theEvent_header, bin, sizeof( ggpDomHeader ) );
    event.SetDomain( (unsigned int)theEvent_header->GetCrystal( ) );
    event.SetTimeStamp( (unsigned int)theEvent_header->GetTstamp( ) );

    if( theEvent_header->IsIdle() || theEvent_header->IsPileUp() ) continue;

    UInt_t ch;
    bool found = false;
    for( ch = 0; ch < SIZE_CHAN; ++ch ){                                                      

      memset( samples, 0, 100 );
      channel = ch;

      memcpy( (char*)theChannel_header, bin + SIZE_HEAD + ch*( SIZE_SHEAD + SIZE_TRACE ), sizeof( ggpSubHeader ) );
      memcpy( (char*)samples, bin + SIZE_HEAD + ch*( SIZE_SHEAD + SIZE_TRACE ) + SIZE_SHEAD, SIZE_TRACE );
      baseline = 0.;
      
      int k;
      float max [ 5 ] = { 0 };
      float maxSig = 0;
      for( k = 0; k < 100; ++k ){

	ftrace[ k ] = float( ( samples[ k ] & 0x3FFF ) ^ 0x2000 );

	if( k > 94 ) max[ ( k - 95 ) ] = ftrace[ k ] ;

	if( k < 15 ) baseline += ftrace[ k ];

      }

      baseline/=15.;

      float sumMax = 0;
      for( k = 0; k < 5; ++k ){
	sumMax = sumMax + max[ k ] - baseline;
      }
      
      maxSig = sumMax/5;
      
      interpolation( ftrace, derivMax, riseTime, baseline, maxSig );

      CFD_filter( ftrace, CFD, CFDzero, baseline, riseTime );
 
      traceEnergy = (float)( theChannel_header->GetEnergy()*1/65536.f );
      if( traceEnergy > 80 && channel == 1 ) found = true;
      else found = false;
      if( std::abs( traceEnergy ) < 65000 ) theTree->Fill( );

      event.SetSubs( (uint16_t)channel, (float)traceEnergy, (float)derivMax,
		      (float)riseTime, (float)baseline, (float)traceEnergy );

      derivMax = 0;
      
    }

    if( found ) ++evCount;
    event.Clear( );
    
  }

  inputFile.close();
  theTree->Write();
  fileOut->Close();
  
}

void CFD_filter( float* trace, float* CFD_trace, float& CFD_zero , float &baseline, double &riseTime ){

  valarray<float> delayed ( trace, 100 );
  valarray<float> invAtt ( trace, 100 );
  delayed -= baseline;
  invAtt -= baseline;

  invAtt *= ( - 0.4 );

  int i;
  int delay = riseTime * 0.8;

  for( i = 0; i < 100; ++i ){
    
    if( ( i + delay ) < 100 ) CFD_trace[ i ] = ( delayed[ i + delay ]  + invAtt[ i ] );

    else CFD_trace[ i ] = 0;
    
    if( CFD_trace[ i - 1 ] < 30 && CFD_trace[ i ] > 30 ) CFD_zero = ( i + i + 1 )/2;

  }

}

void interpolation( float* trace, double &derivMax, double &riseTime, float &baseline, float &maxSig ){

  double data[ 100 ];
  int k;
  for( k = 0; k < 100; ++k){
    data[ k ] = ( (double)trace[ k ] ) - baseline;
  }

  TSpline3 *graph = new TSpline3( "wave", 0, 100, data, 100, 0, 0, 0 );

  float first, second, third;
  first = second = third = 0;
  
  double a = 0;
  double b = 0;
  
  double start = 0;
  double end = 0;
  bool start_f = 0;
  bool end_f = 0;
  
  for( k = 1; k < 100; ++k ){

    if( data[ k ]/maxSig > 0.3 && !start_f ){
      
      a = data[ k ] - data[ k - 1 ];
      b = ( data[ k ] + data[ k - 1 ] - a*( 2*k - 1 ) )/2;
      start = ( maxSig*0.3 - b )/a;
      start_f = true;
	  
    }
    
    if( data[ k ]/maxSig > 0.7 && !end_f ){
      
      a = data[ k ] - data[ k - 1 ];
      b = ( data[ k ] + data[ k - 1 ] - a*( 2*k - 1 ) )/2;
      end = ( maxSig*0.7 - b )/a;
      end_f = true;

    }

    if( k > 15 ){
    
      if( first < graph->Derivative( k ) ){
	
	third = second;
	second = first;
	first = graph->Derivative( k );
      
      }
      
      else if( second < graph->Derivative( k ) ){
      
	third = second;
	second = graph->Derivative( k );
	
      }
      
      else if( third < graph->Derivative( k ) ){
	
	third = graph->Derivative( k );
	
      }

    }
    
  }

  derivMax = ( first + second + third )/3;
  if( ( end - start ) > 0 && ( end - start ) < 100 ) riseTime = ( end - start );
  else riseTime = 0;

  delete graph;
  
}
    
  
  
  
