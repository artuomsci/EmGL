#!/bin/bash

export PLATFORM_TYPE="local"

mkdir ./build_local
cd ./build_local

cmake .. -DCMAKE_BUILD_TYPE=Debug