cmake_minimum_required(VERSION 3.28)

project(dinput8)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /sdl /MP /O2")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /INCREMENTAL:NO")

include_directories(
  "${CMAKE_SOURCE_DIR}/inc/"
  "${CMAKE_SOURCE_DIR}/lib/"
)

link_directories(
  "${CMAKE_SOURCE_DIR}/lib/"
)

file(GLOB_RECURSE SOURCES
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/inc/*.hpp"
)

add_library(dinput8 SHARED ${SOURCES})

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  target_link_libraries(dinput8 "minhook/minhook.x64")
else()
  target_link_libraries(dinput8 "minhook/minhook.x86")
endif()