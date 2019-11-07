#include <fstream>
#include <TGraph.h>
#include <TTree.h>
#include <TMultiGraph.h>

void getRiseTime( ){

  TFile* file = new TFile( "run_4024_gal09.root" );
  TTree* tree = (TTree*)file->Get( "ggpData" );

  TFile* fileOut = new TFile( "riseTime.root", "RECREATE" );
  TTree* treeNew = new TTree( "ggpData", "ggpData" );


  
  float sample [100] = { 0 };
  float energy = 0;
  unsigned short channel = 0;
  float riseTime = 0;
  float baseline = 0;

  treeNew->Branch( "riseTime", &riseTime, "riseTime/F" );
  treeNew->Branch( "energy", &energy, "energy/F" );
  treeNew->Branch( "channel", &channel, "channel/s" );
  
  tree->SetBranchAddress( "samples", sample );
  tree->SetBranchAddress( "energy", &energy );
  tree->SetBranchAddress( "channel", &channel );
  tree->SetBranchAddress( "baseline", &baseline );

  int k;
  for( k = 0; k < tree->GetEntries( ); ++k ){
    
    tree->GetEntry( k );
    
    double data[100] = { 0 };
    double maxSig = 0;
    for( int k = 0; k < 100; ++k){

      data[ k ] = ( (double)sample[ k ] ) - baseline;
      if( maxSig < data[ k ] ) maxSig = data[ k ];
      
    }
    
    TSpline3 *graph = new TSpline3( "wave", 0, 100, data, 100, 0, 0, 0 );

    auto func  = [ & ]( double *x, double * ){ return graph->Eval( x[0] ); };
    auto f1 = new TF1( "f1", func, 0, 100, 0 );
    double end = f1->GetX( maxSig*0.9, 0, 100 );
    double start = f1->GetX( maxSig*0.1, 0, 100 );

    riseTime = ( end - start );
    treeNew->Fill( );

    delete graph;
    delete f1;
    
  }

  file->Close( );
  
  treeNew->Write( );
  fileOut->Close( );
  
}
