# file:     makefile:
# author:   ntietz
# date:     2011.5.26

COMPILER=g++
# COMPILER=clang
COMPILE_OPTS= -std=gnu++0x #-Wall #adds c++0x support, for the random lib
SRC=src
TEST=test
BIN=bin

# META TARGETS

all : clean init compile build_tests run_tests
	

init :
	mkdir bin

compile : chromosome random datagen mergesort bubblesort quicksort converter ga
	

build_tests : bubbletest quicktest mergetest datagentest randomtest gatest
	

# SOURCE TARGETS

mergesort: ${SRC}/common.h ${SRC}/merge/mergesort.h
	${COMPILER} ${COMPILE_OPTS} ${SRC}/merge/mergesort.h

bubblesort: ${SRC}/common.h ${SRC}/bubble/bubblesort.h
	${COMPILER} ${COMPILE_OPTS} ${SRC}/bubble/bubblesort.h

#TODO add dependencies to the following targets

quicksort :
	${COMPILER} ${COMPILE_OPTS} ${SRC}/quick/quicksort.h

chromosome : ${SRC}/chromosome/chromosome.cpp ${SRC}/chromosome/chromosome.hpp
	${COMPILER} ${COMPILE_OPTS} ${SRC}/chromosome/chromosome.cpp -c -o ${BIN}/chromosome.o

converter : ${SRC}/converter/converter.hpp
	${COMPILER} ${COMPILE_OPTS} ${SRC}/converter/converter.hpp -c -o ${BIN}/converter.o

random : lib/SimpleRNG.h lib/SimpleRNG.cpp
	${COMPILER} ${COMPILE_OPTS} lib/SimpleRNG.cpp -c -o ${BIN}/random.o

datagen : src/datagen/datagen.cpp src/datagen/datagen.hpp
	${COMPILER} ${COMPILE_OPTS} src/datagen/datagen.cpp -c -o ${BIN}/datagen.o

ga : src/ga/ga.h
	${COMPILER} ${COMPILE_OPTS} src/ga/ga.h -c -o ${BIN}/ga.o

# TEST TARGETS

mergetest : 
	${COMPILER} ${COMPILE_OPTS} ${TEST}/merge/mergetest.cpp -o ${BIN}/mergetest.out

bubbletest : 
	${COMPILER} ${COMPILE_OPTS} ${TEST}/bubble/bubbletest.cpp -o ${BIN}/bubbletest.out

quicktest : 
	${COMPILER} ${COMPILE_OPTS} ${TEST}/quick/quicktest.cpp -o ${BIN}/quicktest.out

randomtest : 
	${COMPILER} ${COMPILE_OPTS} ${TEST}/random/randomtest.cpp bin/random.o -o ${BIN}/randomtest.out

datagentest :
	${COMPILER} ${COMPILE_OPTS} test/datagen/datagentest.cpp bin/random.o bin/datagen.o -o bin/datagentest.out

gatest :
	${COMPILER} ${COMPILE_OPTS} test/ga/gatest.cpp bin/datagen.o bin/random.o bin/chromosome.o -o bin/gatest.out

run_tests : mergetest bubbletest
	@echo "\nRunning unit tests...\n\n"
	./${BIN}/mergetest.out
	./${BIN}/bubbletest.out
	./${BIN}/quicktest.out
	./${BIN}/randomtest.out
	./${BIN}/datagentest.out
	@echo "\nDone running test.\n"
	

clean : 
	rm -f */*/*.h.gch
	rm -rf bin

