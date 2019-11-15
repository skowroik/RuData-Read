// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TraceEventDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TraceEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TraceSubData_Dictionary();
   static void TraceSubData_TClassManip(TClass*);
   static void *new_TraceSubData(void *p = 0);
   static void *newArray_TraceSubData(Long_t size, void *p);
   static void delete_TraceSubData(void *p);
   static void deleteArray_TraceSubData(void *p);
   static void destruct_TraceSubData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TraceSubData*)
   {
      ::TraceSubData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TraceSubData));
      static ::ROOT::TGenericClassInfo 
         instance("TraceSubData", "TraceEvent.h", 11,
                  typeid(::TraceSubData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TraceSubData_Dictionary, isa_proxy, 4,
                  sizeof(::TraceSubData) );
      instance.SetNew(&new_TraceSubData);
      instance.SetNewArray(&newArray_TraceSubData);
      instance.SetDelete(&delete_TraceSubData);
      instance.SetDeleteArray(&deleteArray_TraceSubData);
      instance.SetDestructor(&destruct_TraceSubData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TraceSubData*)
   {
      return GenerateInitInstanceLocal((::TraceSubData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TraceSubData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TraceSubData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TraceSubData*)0x0)->GetClass();
      TraceSubData_TClassManip(theClass);
   return theClass;
   }

   static void TraceSubData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TraceEvent_Dictionary();
   static void TraceEvent_TClassManip(TClass*);
   static void *new_TraceEvent(void *p = 0);
   static void *newArray_TraceEvent(Long_t size, void *p);
   static void delete_TraceEvent(void *p);
   static void deleteArray_TraceEvent(void *p);
   static void destruct_TraceEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TraceEvent*)
   {
      ::TraceEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TraceEvent));
      static ::ROOT::TGenericClassInfo 
         instance("TraceEvent", "TraceEvent.h", 40,
                  typeid(::TraceEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TraceEvent_Dictionary, isa_proxy, 4,
                  sizeof(::TraceEvent) );
      instance.SetNew(&new_TraceEvent);
      instance.SetNewArray(&newArray_TraceEvent);
      instance.SetDelete(&delete_TraceEvent);
      instance.SetDeleteArray(&deleteArray_TraceEvent);
      instance.SetDestructor(&destruct_TraceEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TraceEvent*)
   {
      return GenerateInitInstanceLocal((::TraceEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TraceEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TraceEvent_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TraceEvent*)0x0)->GetClass();
      TraceEvent_TClassManip(theClass);
   return theClass;
   }

   static void TraceEvent_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_TraceSubData(void *p) {
      return  p ? new(p) ::TraceSubData : new ::TraceSubData;
   }
   static void *newArray_TraceSubData(Long_t nElements, void *p) {
      return p ? new(p) ::TraceSubData[nElements] : new ::TraceSubData[nElements];
   }
   // Wrapper around operator delete
   static void delete_TraceSubData(void *p) {
      delete ((::TraceSubData*)p);
   }
   static void deleteArray_TraceSubData(void *p) {
      delete [] ((::TraceSubData*)p);
   }
   static void destruct_TraceSubData(void *p) {
      typedef ::TraceSubData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TraceSubData

namespace ROOT {
   // Wrappers around operator new
   static void *new_TraceEvent(void *p) {
      return  p ? new(p) ::TraceEvent : new ::TraceEvent;
   }
   static void *newArray_TraceEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TraceEvent[nElements] : new ::TraceEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TraceEvent(void *p) {
      delete ((::TraceEvent*)p);
   }
   static void deleteArray_TraceEvent(void *p) {
      delete [] ((::TraceEvent*)p);
   }
   static void destruct_TraceEvent(void *p) {
      typedef ::TraceEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TraceEvent

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 339,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 339,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlETraceSubDatagR_Dictionary();
   static void vectorlETraceSubDatagR_TClassManip(TClass*);
   static void *new_vectorlETraceSubDatagR(void *p = 0);
   static void *newArray_vectorlETraceSubDatagR(Long_t size, void *p);
   static void delete_vectorlETraceSubDatagR(void *p);
   static void deleteArray_vectorlETraceSubDatagR(void *p);
   static void destruct_vectorlETraceSubDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TraceSubData>*)
   {
      vector<TraceSubData> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TraceSubData>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TraceSubData>", -2, "vector", 339,
                  typeid(vector<TraceSubData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETraceSubDatagR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TraceSubData>) );
      instance.SetNew(&new_vectorlETraceSubDatagR);
      instance.SetNewArray(&newArray_vectorlETraceSubDatagR);
      instance.SetDelete(&delete_vectorlETraceSubDatagR);
      instance.SetDeleteArray(&deleteArray_vectorlETraceSubDatagR);
      instance.SetDestructor(&destruct_vectorlETraceSubDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TraceSubData> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TraceSubData>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETraceSubDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TraceSubData>*)0x0)->GetClass();
      vectorlETraceSubDatagR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETraceSubDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETraceSubDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TraceSubData> : new vector<TraceSubData>;
   }
   static void *newArray_vectorlETraceSubDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TraceSubData>[nElements] : new vector<TraceSubData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETraceSubDatagR(void *p) {
      delete ((vector<TraceSubData>*)p);
   }
   static void deleteArray_vectorlETraceSubDatagR(void *p) {
      delete [] ((vector<TraceSubData>*)p);
   }
   static void destruct_vectorlETraceSubDatagR(void *p) {
      typedef vector<TraceSubData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TraceSubData>

namespace ROOT {
   static TClass *vectorlETraceEventgR_Dictionary();
   static void vectorlETraceEventgR_TClassManip(TClass*);
   static void *new_vectorlETraceEventgR(void *p = 0);
   static void *newArray_vectorlETraceEventgR(Long_t size, void *p);
   static void delete_vectorlETraceEventgR(void *p);
   static void deleteArray_vectorlETraceEventgR(void *p);
   static void destruct_vectorlETraceEventgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TraceEvent>*)
   {
      vector<TraceEvent> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TraceEvent>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TraceEvent>", -2, "vector", 339,
                  typeid(vector<TraceEvent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETraceEventgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TraceEvent>) );
      instance.SetNew(&new_vectorlETraceEventgR);
      instance.SetNewArray(&newArray_vectorlETraceEventgR);
      instance.SetDelete(&delete_vectorlETraceEventgR);
      instance.SetDeleteArray(&deleteArray_vectorlETraceEventgR);
      instance.SetDestructor(&destruct_vectorlETraceEventgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TraceEvent> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TraceEvent>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETraceEventgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TraceEvent>*)0x0)->GetClass();
      vectorlETraceEventgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETraceEventgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETraceEventgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TraceEvent> : new vector<TraceEvent>;
   }
   static void *newArray_vectorlETraceEventgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TraceEvent>[nElements] : new vector<TraceEvent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETraceEventgR(void *p) {
      delete ((vector<TraceEvent>*)p);
   }
   static void deleteArray_vectorlETraceEventgR(void *p) {
      delete [] ((vector<TraceEvent>*)p);
   }
   static void destruct_vectorlETraceEventgR(void *p) {
      typedef vector<TraceEvent> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TraceEvent>

namespace {
  void TriggerDictionaryInitialization_TraceEventDict_Impl() {
    static const char* headers[] = {
"TraceEvent.h",
0
    };
    static const char* includePaths[] = {
"/home/kuba/build/include",
"/home/kuba/build/include/",
"/home/kuba/Desktop/lab2/dev/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TraceEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TraceEvent.h")))  TraceSubData;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$TraceEvent.h")))  TraceEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TraceEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TraceEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"TraceEvent", payloadCode, "@",
"TraceSubData", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TraceEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TraceEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TraceEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TraceEventDict() {
  TriggerDictionaryInitialization_TraceEventDict_Impl();
}
