//#ifndef Event_h
//#define Event_h

#include <vector>
#include <cstdint>                       // for 32 bit integers

#include <TObject.h>

class Event : public TObject {

 public:

  unsigned long evNumber;                    // event number 32 bit
  unsigned short timeStamp [3];         // timestamp 48 bit
  unsigned short sampleNumber;          // sample number 16 bit
  unsigned short frameLenght;           // frame lenght 16 bit
  unsigned short digitId;               // digitizer ID 16 bit
  unsigned short statusHead;            // status 16 bit

  unsigned long energy [36];                 // energy array for every channel, 32 bit each
  unsigned short statusChan [36];       // status array for every channel, 16 bit each

  unsigned short waveSignal [36][99];       // sample data

  ClassDef( Event, 1 )

 private:

};

#if !defined(__CINT__)
ClassImp(Event);

#endif
