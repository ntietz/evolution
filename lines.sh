#!/bin/bash

find . | grep -v "^\./\.git" | grep -v "\.swp$" | grep -v "lib\|samples\|test" | grep "\.cpp\|\.hpp\|\.h$" | xargs wc -l

