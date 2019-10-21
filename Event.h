#ifndef Event_h
#define Event_h

#include <vector>
#include <cstdint>                       // for 32 bit integers

class Event {

 public:

  uint32_t evNumber;                    // event number 32 bit
  unsigned short timeStamp [3];         // timestamp 48 bit
  unsigned short sampleNumber;          // sample number 16 bit
  unsigned short frameLenght;           // frame lenght 16 bit
  unsigned short digitId;               // digitizer ID 16 bit
  unsigned short statusHead;            // status 16 bit

  uint32_t energy [36];                 // energy array for every channel, 32 bit each
  unsigned short statusChan [36];       // status array for every channel, 16 bit each

 private:

};

#endif
