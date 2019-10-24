#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <TFile.h>
#include <TTree.h>

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

void readRuData( string inFile, string outFile, ULong64_t nEvents ){

  ifstream inputFile;
  inputFile.open( inFile.c_str() , std::ios::binary );                // opening the file
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
  float riseTime;
  
  const int SIZE_CHAN = 36;                                                         // variables to divide binary data
  const int SIZE_HEAD = sizeof( ggpDomHeader );
  const int SIZE_SHEAD = sizeof( ggpSubHeader );
  const int SIZE_TRACE = 100 * sizeof( uint16_t );

  int EV_SIZE = SIZE_HEAD + ( SIZE_SHEAD + SIZE_TRACE )*( SIZE_CHAN );;                // Event size


  TFile *fileOut =  new TFile( outFile.c_str(),"recreate" );                       // to write on root file
  TTree *theTree = new TTree( "ggpData","ggpData" );
  unsigned short *theBuffer;
  theTree->Branch( "channel", &channel, "channel/s" );
  theTree->Branch( "energy", &traceEnergy, "energy/F" );
  theTree->Branch( "samples", ftrace, "samples[100]/F" );
  theTree->Branch( "baseline", &baseline, "baseline/F" );
  theTree->Branch( "riseTime", &riseTime, "riseTime/F" );
  
  ggpDomHeader *theEvent_header = new ggpDomHeader;                                 // structs pointers
  ggpSubHeader *theChannel_header = new ggpSubHeader;                                                       
  char bin [ EV_SIZE ];

  int evCount = 0;
  
  while( inputFile.read( bin , sizeof( bin ) ) ){

    if( nEvents > 0 && evCount > nEvents) break;

    theBuffer = ( unsigned short* )bin;

    memcpy( (char*)theEvent_header, bin, sizeof( ggpDomHeader ) );

    if( theEvent_header->IsIdle() || theEvent_header->IsPileUp() ) continue;

    UInt_t ch;
    for( ch = 0; ch < SIZE_CHAN; ++ch ){                                                      

      memset( samples, 0, 100 );
      channel = ch;

      memcpy( (char*)theChannel_header, bin + SIZE_HEAD + ch*( SIZE_SHEAD + SIZE_TRACE ), sizeof( ggpSubHeader ) );
      memcpy( (char*)samples, bin + SIZE_HEAD + ch*( SIZE_SHEAD + SIZE_TRACE ) + SIZE_SHEAD, SIZE_TRACE );
      baseline = 0.;
      
      int k;
      float maxSig = 0;
      for( k = 0; k < 100; ++k ){

	ftrace[ k ] = float( ( samples[ k ] & 0x3FFF ) ^ 0x2000 );
	
	if( maxSig < ftrace[ k ] ) maxSig = ftrace[ k ] ;

	if( k < 15 ) baseline += ftrace[ k ];

      }

      baseline/=15.;
      
      int first = 0;
      int second = 0;
      for( k = 0; k < 100; ++k ){

	if( first == 0 && ( ftrace[ k ] - baseline )/( maxSig - baseline ) > 0.1 ) first = k;

        if( second == 0 && ( ftrace[ k ] - baseline )/( maxSig - baseline ) > 0.9 ) second = k;

      }

      riseTime = second - first;
      
      

      traceEnergy = (float)( theChannel_header->GetEnergy()*1/65536.f );

      if( abs( traceEnergy ) < 65000 ) theTree->Fill();
      
    }

    ++evCount;
    
  }

  inputFile.close();
  theTree->Write();
  fileOut->Close();
  
}
