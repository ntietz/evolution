# file:     makefile:
# author:   ntietz
# date:     2011.5.26

COMPILE_OPTS= -Wall
SRC=src
TEST=test
BIN=bin

all : clean init mergesort mergetest bubblesort bubbletest
	

init :
	mkdir bin

mergesort: ${SRC}/common.h ${SRC}/merge/*
	g++ ${COMPILE_OPTS} ${SRC}/merge/mergesort.h

mergetest : 
	g++ ${COMPILE_OPTS} ${TEST}/merge/mergetest.cpp -o ${BIN}/mergetest.out
	./${BIN}/mergetest.out

bubblesort: ${SRC}/common.h ${SRC}/bubble/*
	g++ ${COMPILE_OPTS} ${SRC}/bubble/bubblesort.h

bubbletest : 
	g++ ${COMPILE_OPTS} ${TEST}/bubble/bubbletest.cpp -o ${BIN}/bubbletest.out
	./${BIN}/bubbletest.out


clean : 
	rm -f */*/*.h.gch
	rm -rf bin

