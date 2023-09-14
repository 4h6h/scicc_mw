#!/usr/bin/bash

rm -rf "build"
mkdir -p "build"
cd "build"
cmake "../" -D"CMAKE_BUILD_TYPE=Debug"

make -j8