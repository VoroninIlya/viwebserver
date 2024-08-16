#!/bin/bash

lcov -t "tst_viwebserver -o tst_viwebserver.info -c -d .
genhtml -o report tst_viwebserver.info