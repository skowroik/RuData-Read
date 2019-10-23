#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "Event.h"
#include "TFile.h"
#include "TTree.h"
#include "TClass.h"
#include "TObject.h"

using namespace std;

void readRuData(){
  
  const int SIZE_CHAN = 36;                                                         // variables to divide binary data
  const int SIZE_HEAD = 16;
  const int SIZE_SUB_HEAD = 8;
  const int SIZE_SUB_DOM = 100;

  int EV_SIZE = SIZE_HEAD + ( ( SIZE_SUB_HEAD + SIZE_SUB_DOM )* ( SIZE_CHAN ) );    // Event size
  
  ifstream file;
  file.open( "rudata_gal-09_ru4_s87_r4036.i1", std::ios::binary );                  // opening the file

  //  ofstream output;
  //  output.open( "out_prova" );                                                       // an output to print whatever

  Event* ev;                                                                        // creating an Event
  char bin [ EV_SIZE*2 ];                                                           // char array to contain binary data (multiply by 2 because every word is 16 bit, not 8)

  unsigned short data;

  TFile rootData("data.root", "RECREATE");

  int count = 0;
  
  while( !file.eof() ){

    ev = new Event;

    TTree *tree = new TTree("T","An example of a ROOT tree");

    file.read( bin , sizeof( bin ) );                                              // reading binary data

    memcpy( &ev->evNumber, bin + 2, sizeof( ev->evNumber ) );                      // coping data to different variables
    memcpy( &ev->timeStamp, bin + 6, sizeof( ev->timeStamp ) );
    memcpy( &ev->sampleNumber, bin + 12, sizeof( ev->sampleNumber ) );
    memcpy( &ev->frameLenght, bin + 14, sizeof( ev->frameLenght ) );
    memcpy( &ev->digitId, bin + 16, sizeof( ev->digitId ) );
    memcpy( &ev->statusHead, bin + 18, sizeof( ev->statusHead ) );

    int i;
    for( i = 0; i < 36; ++i ){                                                      // reading data for each channel
      
      memcpy( &ev->energy[i], bin + 32 + ( i*108*2 ), sizeof( ev->energy[i] ) );
      memcpy( &ev->statusChan[i], bin + 36 + ( i*108*2 ), sizeof( ev->statusChan[i] ) );

      int k;
      for( k = 2; k < 200; k = k + 2 ){

	memcpy( &ev->waveSignal[i][ ( ( k/2 ) - 1 ) ], bin + 48 + k + ( i*108*2 ), sizeof( ev->waveSignal[i][ ( ( k/2 ) - 1 ) ] ) );

      }
      
    }
    
    tree->Branch( "Event", &ev );
    tree->Fill( );
    tree->Write( );
    
    delete ev;                                                                     // clearing the memory

    ++count;

    if( count == 100 ) break;
    
  }

  //  rootData.Close();
  
  //  return 0;
  
}
