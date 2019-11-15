#ifndef TRACE_EVENT_H_INCLUDED
#define TRACE_EVENT_H_INCLUDED


#include <map>
#include <vector>
#include <climits>



class TraceSubData{
 public:
  TraceSubData(){};
  ~TraceSubData(){};

 public:
  void SetSubDom   (uint16_t v){fSubDomain = v;} 
  void SetEnergy   (float v)   {fEnergy    = v;}
  void SetTrace    (float v)   {fTrace     = v;}
  void SetTime     (float v)   {fTime      = v;}
  void SetBaseline (float v)   {fBaseline  = v;}
  void SetPSA      (float v)   {fPSA       = v;}

  uint16_t GetSubDom()   {return fSubDomain;}
  float    GetEnergy()   {return fEnergy;   }
  float    GetTrace()    {return fTrace;    }
  float    GetTime()     {return fTime ;    }
  float    GetBaseline() {return fBaseline; }
  float    GetPSA()      {return fPSA     ; }
  
 private:
  uint16_t fSubDomain ; 
  float    fEnergy    ;
  float    fTrace     ;
  float    fTime      ;
  float    fBaseline  ;
  float    fPSA       ;
};

class TraceEvent {
    
public:
    TraceEvent(){
      fSubData.clear();
      fTimeStamp = 0;
      fDomain    = UINT_MAX;
    }
    ~TraceEvent(){;}
    
public:
    void Clear() {fSubData.clear();}
    uint32_t GetSize() {return fSubData.size();}
    void SetSubs          (uint16_t dom, float eAmpli,
			   float wAmpli, float trTime,
			   float bsLine, float xEnergy)
    {
      TraceSubData tmp_evt;
      tmp_evt.SetSubDom   ( dom    );
      tmp_evt.SetEnergy   ( eAmpli );
      tmp_evt.SetTrace    ( wAmpli );
      tmp_evt.SetTime     ( trTime );
      tmp_evt.SetBaseline ( bsLine );
      tmp_evt.SetPSA      (xEnergy );
      fSubData.push_back(tmp_evt);
    }
    void SetDomain        (unsigned int det){fDomain = det       ;}
    void SetTimeStamp     (unsigned int ts) {fTimeStamp = ts     ;}
  
    std::vector<TraceSubData> GetSubData() {return fSubData     ;}
    unsigned int  GetDomain()              {return fDomain      ;}
    unsigned int  GetTimeStamp()           {return fTimeStamp   ;}
    
private:

    std::vector<TraceSubData> fSubData    ;
    unsigned int              fTimeStamp  ;   
    unsigned int              fDomain     ;
};

#endif
