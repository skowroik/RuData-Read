#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

struct Event {				       // struct for Event data
  vector<int> bit_data;
};

int main(){

  const int SIZE_CHAN = 36;
  unsigned short data;
  char bin[ sizeof( short ) ];
  int chan;

  cout << "Which channel? ";
  cin >> chan;
  
  ifstream file;
  file.open( "rudata_gal-09_ru4_s87_r4036.i1", std::ios::binary );

  ofstream output;
  output.open( "out_prova" );

  for( int i = 0; i < 100000; ++i ){
  
    for( int k = 0; k < SIZE_CHAN; ++k ){
      
      file.read( bin , sizeof( bin ) );
      memcpy( &data, bin, sizeof( data ) );
      
      if ( k == chan ) output << data << endl;
      
    }

  }
  
  return 0;
  
}
