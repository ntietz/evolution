# file:     makefile:
# author:   ntietz
# date:     2011.5.26

COMPILE_OPTS= -Wall -std=gnu++0x #adds c++0x support, for the random lib
SRC=src
TEST=test
BIN=bin

# META TARGETS

all : clean init compile build_tests run_tests
	

init :
	mkdir bin

compile : chromosome mergesort mergetest bubblesort bubbletest quicksort converter
	

build_tests : bubbletest quicktest mergetest
	

# SOURCE TARGETS

mergesort: ${SRC}/common.h ${SRC}/merge/mergesort.h
	g++ ${COMPILE_OPTS} ${SRC}/merge/mergesort.h

bubblesort: ${SRC}/common.h ${SRC}/bubble/bubblesort.h
	g++ ${COMPILE_OPTS} ${SRC}/bubble/bubblesort.h

#TODO add dependencies to the following targets

quicksort :
	g++ ${COMPILE_OPTS} ${SRC}/quick/quicksort.h

chromosome : ${SRC}/chromosome/chromosome.cpp ${SRC}/chromosome/chromosome.hpp
	g++ ${COMPILE_OPTS} ${SRC}/chromosome/chromosome.cpp -c -o ${BIN}/chromosome.o

converter : ${SRC}/converter/converter.cpp ${SRC}/converter/converter.hpp
	g++ ${COMPILE_OPTS} ${SRC}/converter/converter.cpp -c -o ${BIN}/converter.o

random : ${SRC}/random/random.cpp ${SRC}/random/random.hpp
	g++ ${COMPILE_OPTS} ${SRC}/random/random.cpp -c -o ${BIN}/random.o

# TEST TARGETS

mergetest : 
	g++ ${COMPILE_OPTS} ${TEST}/merge/mergetest.cpp -o ${BIN}/mergetest.out

bubbletest : 
	g++ ${COMPILE_OPTS} ${TEST}/bubble/bubbletest.cpp -o ${BIN}/bubbletest.out

quicktest : 
	g++ ${COMPILE_OPTS} ${TEST}/quick/quicktest.cpp -o ${BIN}/quicktest.out

randomtest : 
	g++ ${COMPILE_OPTS} ${TEST}/random/randomtest.cpp -o ${BIN}/randomtest.out


run_tests : mergetest bubbletest
	@echo "\nRunning unit tests...\n\n"
	./${BIN}/mergetest.out
	./${BIN}/bubbletest.out
	./${BIN}/quicktest.out
	./${BIN}/randomtest.out
	@echo "\nDone running test.\n"
	

clean : 
	rm -f */*/*.h.gch
	rm -rf bin

