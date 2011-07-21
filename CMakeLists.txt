# Copyright (C) 2011 Casey Marshall

cmake_minimum_required(VERSION 2.8)
PROJECT(skeinsum)
set (VERSION, 0.0.1)
set (SKEIN3FISH_VERSION 0.6.0)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/Skein3Fish/c/src/include)

add_definitions(-g -O2)

include(FindPkgConfig)
include(CheckIncludeFiles)

check_include_files(stdio.h HAVE_STDIO_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(stddef.h HAVE_STDDEF_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(getopt.h HAVE_GETOPT_H)

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-Wno-long-long -Wno-char-subscripts)
  add_definitions(-Wall -ansi -pedantic)
endif()

set(skeinBlock_src Skein3Fish/c/src/skeinBlockNo3F.c)

set(skein_src 
    ${skeinBlock_src}
    Skein3Fish/c/src/skein.c
    Skein3Fish/c/src/skeinApi.c
    )

set(threefish_src
    Skein3Fish/c/src/threefishApi.c
    Skein3Fish/c/src/threefish256Block.c
    Skein3Fish/c/src/threefish512Block.c
    Skein3Fish/c/src/threefish1024Block.c
    )

set(skeinsum_src skeinsum.c)

add_executable(skeinsum ${skein_src} ${threefish_src} ${skeinsum_src})

install(TARGETS skeinsum DESTINATION bin)