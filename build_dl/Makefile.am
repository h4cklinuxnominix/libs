lib_LIBRARIES=libhack_dl.a
libhack_dl_a_SOURCES=../dl/dl.cpp
libhack_dl_a_CPPFLAGS=-ldl

bin_PROGRAMS=dlrun
dlrun_SOURCES=../test/dlload.cpp
dlrun_LDFLAGS= -L./ -lhack_dl
