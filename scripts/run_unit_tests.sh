#!/bin/bash
set -e
DIR="$(pwd)"
PROJECT_NAME=$(cat ${DIR}/CMakeLists.txt | grep -Po "(?<=project\().*(?=\))" )

if [ -d "build_test" ];
then
    rm -rf build_test/*
else
    mkdir -p build_test
fi

cd build_test
cmake -DBUILD_TESTS=ON ..
make -j $(($(nproc) - 1))

./tests/test_${PROJECT_NAME}
