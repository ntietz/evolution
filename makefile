# file:     makefile:
# author:   ntietz
# date:     2011.5.26

COMPILE_OPTS= -Wall
SRC=src
TEST=test
BIN=bin

all : init mergesort mergetest
	

init :
	mkdir bin

mergesort: ${SRC}/common.h ${SRC}/merge/*
	g++ ${COMPILE_OPTS} ${SRC}/merge/mergesort.h

mergetest : 
	g++ ${COMPILE_OPTS} ${TEST}/merge/mergetest.cpp -o ${BIN}/mergetest.out
	./${BIN}/mergetest.out

clean : 
	rm -f */*/*.h.gch
	rm -f bin

