#include <fstream>
#include <TGraph.h>
#include <TTree.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TSystem.h>
void getRiseTime( string inFile ){

  TFile* file = new TFile( inFile.c_str() );
  TTree* tree = (TTree*)file->Get( "ggpData" );

  TFile* fileOut = new TFile( "riseTime.root", "UPDATE" );
  TTree* treeNew = new TTree( "ggpData", "ggpData" );
  TGraph *graphSig = new TGraph( );
  TGraph *graphStartStop = new TGraph( );

   
  float sample [ 100 ] = { 0 };
  float energy = 0;
  unsigned short channel = 0;
  float riseTime = 0;
  float baseline = 0;
  TCanvas *c1= new TCanvas("c1","c1");
  treeNew->Branch( "riseTime", &riseTime, "riseTime/F" );
  treeNew->Branch( "energy", &energy, "energy/F" );
  treeNew->Branch( "channel", &channel, "channel/s" );
  
  tree->SetBranchAddress( "samples", sample );
  tree->SetBranchAddress( "energy", &energy );
  tree->SetBranchAddress( "channel", &channel );
  tree->SetBranchAddress( "baseline", &baseline );

  bool analysis = false;
  
  int i;
  for( i = 0; i < tree->GetEntries( ); ++i ){
    
    tree->GetEntry( i );

    if( channel == 1 ){
      if( energy > 80 ) analysis = true;
      else analysis = false;
    }

    if( analysis ){
      if( energy > 80 ){
	
	double data[100] = { 0 };
	double max [ 5 ] = { 0 };
	double maxSig = 0;
	int k;
	for( k = 0; k < 100; ++k){
	  
	  data[ k ] = ( (double)sample[ k ] ) - baseline;
	  graphSig->SetPoint(k,k,data[k]);
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
    
  }
  
  /*
    TGrSpline3 *graph = new TSpline3( "wave", 0, 100, data, 100, 0, 0, 0 );
    auto func  = [ & ]( double *x, double * ){cout << x[0] << endl; return graph->Eval( x[0] ); };
    auto f1 = new TF1( "f1", func, 0, 100, 0 );
    double end = f1->GetX( maxSig*0.9, 0, 100 );
    double start = f1->GetX( maxSig*0.1, 0, 100 );
  */
  
  //	riseTime = ( end - start );
  //	treeNew->Fill( );
  
  //	delete graph;
  //	delete f1;
  
  file->Close( );
  
  treeNew->Write( );
  fileOut->Close( );
  
}
