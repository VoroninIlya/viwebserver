#!/bin/bash

./build/Win64-Debug/tst_viwebserver.exe

lcov -t "tst_viwebserver" --derive-func-data --capture --directory ./build --output-file tst_viwebserver_raw.info 

lcov --remove tst_viwebserver_raw.info *msys64* *gtest* --output-file tst_viwebserver.info

genhtml tst_viwebserver.info --function-coverage --branch-coverage --highlight --prefix ./report --output-directory ./report
