#!/bin/bash

find . | grep -v "^\./\.git" | grep -v "lib" | grep "\.cpp$\|\.hpp$\|\.h$" | xargs wc -l

