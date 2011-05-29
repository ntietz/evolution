# file:     makefile:
# author:   ntietz
# date:     2011.5.26

COMPILE_OPTS= -Wall
SRC=src
TEST=test
BIN=bin

all : clean init mergesort mergetest bubblesort bubbletest quicksort quicktest run_tests
	

init :
	mkdir bin

mergesort: ${SRC}/common.h ${SRC}/merge/mergesort.h
	g++ ${COMPILE_OPTS} ${SRC}/merge/mergesort.h

mergetest : 
	g++ ${COMPILE_OPTS} ${TEST}/merge/mergetest.cpp -o ${BIN}/mergetest.out

bubblesort: ${SRC}/common.h ${SRC}/bubble/bubblesort.h
	g++ ${COMPILE_OPTS} ${SRC}/bubble/bubblesort.h

bubbletest : 
	g++ ${COMPILE_OPTS} ${TEST}/bubble/bubbletest.cpp -o ${BIN}/bubbletest.out

quicksort :
	g++ ${COMPILE_OPTS} ${SRC}/quick/quicksort.h

quicktest : 
	g++ ${COMPILE_OPTS} ${TEST}/quick/quicktest.cpp -o ${BIN}/quicktest.out


run_tests : mergetest bubbletest
	@echo "\nRunning unit tests...\n\n"
	./${BIN}/mergetest.out
	./${BIN}/bubbletest.out
	./${BIN}/quicktest.out
	@echo "\nDone running test.\n"
	

clean : 
	rm -f */*/*.h.gch
	rm -rf bin

