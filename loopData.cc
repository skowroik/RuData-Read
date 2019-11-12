#include <fstream>
#include <TGraph.h>
#include <TTree.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TSystem.h>
#include<TString.h>

void getCleanData( TFile* fileOut, TTree* treeNew, const char* filename );

void loopData( ){

  TFile* fileOut = new TFile( "cleanData.root", "RECREATE" );
  TTree* treeNew = new TTree( "ggpData", "ggpData" );
  //  TCanvas *c1= new TCanvas("c1","c1");
  //  TGraph *graphSig = new TGraph( );
  //  TGraph *graphStartStop = new TGraph( );
  
  const char* ext = ".root";
  const char* inDir = "/home/kuba/Desktop/lab2/data";

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

  for (Int_t a = 0; a < l; ++a) getCleanData( fileOut, treeNew, filename[ a ] );

  fileOut->cd( );
  treeNew->Write( );
  fileOut->Close( );
  
}

void getCleanData( TFile* fileOut, TTree* treeNew, const char* filename ){
    
  TFile* file = new TFile( filename );;
  TTree* tree = (TTree*)file->Get( "ggpData" );

  float sample [ 100 ] = { 0 };
  float energy = 0;
  unsigned short channel = 0;
  float riseTime = 0;
  double iMax = 0;
  float baseline = 0;
  treeNew->Branch( "riseTime", &riseTime, "riseTime/F" );
  treeNew->Branch( "iMax", &iMax, "iMax/D" );
  treeNew->Branch( "energy", &energy, "energy/F" );
  treeNew->Branch( "channel", &channel, "channel/s" );
    
    
    
  tree->SetBranchAddress( "samples", sample );
  tree->SetBranchAddress( "energy", &energy );
  tree->SetBranchAddress( "channel", &channel );
  tree->SetBranchAddress( "baseline", &baseline );
  tree->SetBranchAddress( "iMax", &iMax );
  
  bool analysis = false;
  
  int i;
  for( i = 0; i < tree->GetEntries( ); ++i ){
    
    tree->GetEntry( i );
    
    if( channel == 1 ){
      if( energy > 80 ) analysis = true;
      
      else analysis = false;
    }
    
    if( analysis && energy > 80 ){
      
      double data[100] = { 0 };
      double max [ 5 ] = { 0 };
      double maxSig = 0;
      int k;
      for( k = 0; k < 100; ++k){
	
	data[ k ] = ( (double)sample[ k ] ) - baseline;
	//	  graphSig->SetPoint(k,k,data[k]);
	if( k > 94 ) max[ ( k - 95 ) ] = data[ k ];
	  
      }
      
      double sum = 0;
      for( k = 0; k < 5; ++k ){
	sum = sum + max[ k ];
      }
      
      maxSig = sum/5;
      
      
      
      double a = 0;
      double b = 0;
      double start = 0;
      double end = 0;
      bool start_f = 0;
      bool end_f = 0;
      for( k = 0; k < 100; ++k){
	
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
	
	if(start_f && end_f) break;
	
      }
      
      /*
	if( maxSig > 500 ){
	graphStartStop->SetPoint(0,start,0.3*maxSig);
	graphStartStop->SetPoint(1,end  ,0.7*maxSig);
	graphSig->Draw("al");
	graphStartStop->SetMarkerStyle(20);
	graphStartStop->SetMarkerColor(kRed);
	graphStartStop->Draw("p");
	
	c1->Update();
	gSystem->Sleep(1000);
	}
      */

      riseTime = end - start;
      
      treeNew->Fill( );
      
    }
    
  }

  file->Close( );
  
}
