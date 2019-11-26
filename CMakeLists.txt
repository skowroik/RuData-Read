cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(readTraceEvent)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIR})

find_package(Torch REQUIRED)
add_executable(readTraceEvent readTraceEvent.cc)

ROOT_GENERATE_DICTIONARY(TraceEventDict TraceEvent.h LINKDEF TraceEventLinkDef.h)
add_library(TraceEvent SHARED TraceEventDict.cxx)

target_link_libraries(readTraceEvent "${TORCH_LIBRARIES}" "${ROOT_LIBRARIES}" "-Wl,--no-as-needed" TraceEvent)
set_property(TARGET readTraceEvent PROPERTY CXX_STANDARD 11)
