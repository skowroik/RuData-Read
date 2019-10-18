#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct Event {				       // struct for Event data
  vector<int> bit_data;
};

int main(){

  const int SIZE_CHAN = 36;
  const int SIZE_HEAD = 16;
  const int SIZE_SUB_HEAD = 8;
  const int SIZE_SUB_DOM = 100;

  int EV_SIZE = SIZE_HEAD + ( ( SIZE_SUB_HEAD + SIZE_SUB_DOM )* ( SIZE_CHAN ) );
  
  char bin[ EV_SIZE*2 ];
  unsigned long data;
  
  ifstream file;
  file.open( "rudata_gal-09_ru4_s87_r4036.i1", std::ios::binary );

  ofstream output;
  output.open( "out_prova" );

  while( !file.eof() ){
  
    file.read( bin , sizeof( bin ) );

    memcpy( &data, bin + 34, sizeof( data ) );
      
    output << data << endl;
      
  }
  
  return 0;
  
}
