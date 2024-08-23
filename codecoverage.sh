#!/bin/bash

./build/Win64-Debug/tst_viwebserver.exe

lcov -t "tst_viwebserver" --output-file tst_viwebserver.info --derive-func-data --capture --directory ./build

genhtml tst_viwebserver.info --function-coverage --branch-coverage --highlight --prefix ./report --output-directory ./report
