cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

project("AjnaSpeak")

################################
# Add additional compiler flags #
#################################

IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++ -Wno-deprecated-declarations -Wno-unused-function")
ENDIF()

IF(NOT WIN32)
  SET(CFLAGS_WARN "-Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing")
  SET(CMAKE_CXX_FLAGS "-fPIC -O3 -march=native ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
  #SET(CMAKE_CXX_FLAGS "-fPIC -g ${CFLAGS_WARN} ${CMAKE_CXX_FLAGS}")
ENDIF()

#########################
# Suppress auto-linking #
#########################

IF(WIN32)
  ADD_DEFINITIONS(-DUSING_CMAKE=1)
ENDIF()


############# Find ESPEAK TTS ############

find_path(LIBESPEAK_INCLUDE_DIRS
          NAMES speak_lib.h
          HINTS /usr/local/include/espeak
          $CMAKE_CURRENT_SOURCE_DIR )

link_directories(/usr/lib/x86_64-linux-gnu)

#########################################
include_directories(include)
#include_directories($LIBESPEAK_INCLUDE_DIRS)

file(GLOB SOURCES_CPP "src/*.cpp")
file(GLOB SOURCES_H "include/*.h")

add_executable(AjnaSpeak
        ${SOURCES_CPP}
        ${SOURCES_H}
    )


target_link_libraries(AjnaSpeak
    ${eSpeak_LIBRARIES}
    espeak
    -lpthread
)
