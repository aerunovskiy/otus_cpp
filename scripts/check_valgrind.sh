#!/bin/bash

set -e
DIR="$(pwd)"
PROJECT_NAME=$(cat ${DIR}/CMakeLists.txt | grep -Po "(?<=project\().*(?=\))" )

if [ -d "build" ];
then
    rm -rf build/*
else
    mkdir -p build
fi

cd build
cmake -DBUILD_TESTS=OFF ..
make -j $(($(nproc) - 1))

valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.log ./${PROJECT_NAME}

if grep -q "ERROR SUMMARY: 0 errors" valgrind.log; then
  echo "No errors found"
else
  echo "Errors found"
  exit 1
fi

