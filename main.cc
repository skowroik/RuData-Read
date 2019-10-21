#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

#include "Event.h"

using namespace std;

int main(){

  const int SIZE_CHAN = 36;                                                         // variables to divide binary data
  const int SIZE_HEAD = 16;
  const int SIZE_SUB_HEAD = 8;
  const int SIZE_SUB_DOM = 100;

  int EV_SIZE = SIZE_HEAD + ( ( SIZE_SUB_HEAD + SIZE_SUB_DOM )* ( SIZE_CHAN ) );    // Event size
  
  ifstream file;
  file.open( "rudata_gal-09_ru4_s87_r4036.i1", std::ios::binary );                  // opening the file

  ofstream output;
  output.open( "out_prova" );                                                       // an output to print whatever

  Event* ev;                                                                        // creating an Event
  char bin [ EV_SIZE*2 ];                                                           // char array to contain binary data (multiply by 2 because every word is 16 bit, not 8)
  

  while( !file.eof() ){

    ev = new Event;
    
    file.read( bin , sizeof( bin ) );                                              // reading binary data

    memcpy( &ev->evNumber, bin + 2, sizeof( ev->evNumber ) );                      // coping data to different variables
    memcpy( &ev->timeStamp, bin + 6, sizeof( ev->timeStamp ) );
    memcpy( &ev->sampleNumber, bin + 12, sizeof( ev->sampleNumber ) );
    memcpy( &ev->frameLenght, bin + 14, sizeof( ev->frameLenght ) );
    memcpy( &ev->digitId, bin + 16, sizeof( ev->digitId ) );
    memcpy( &ev->statusHead, bin + 18, sizeof( ev->statusHead ) );

    int i;
    for( i = 0; i < 36; ++i){                                                      // reading data for each channel
      
      memcpy( &ev->energy[i], bin + 32 + ( i*108*2 ), sizeof( ev->energy[i] ) );
      memcpy( &ev->statusChan[i], bin + 36 + ( i*108*2 ), sizeof( ev->statusChan[i] ) );

    }

    //    output <<  << endl;                                                      // printing on file
    
    delete ev;                                                                     // clearing the memory 
      
  }
  
  return 0;
  
}
