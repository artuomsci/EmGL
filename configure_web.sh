#!/bin/bash

export PLATFORM_TYPE="web"

EMCMAKE_PATH=$(find $HOME -iname 'emcmake' -printf %h)

export PATH=$PATH:$EMCMAKE_PATH

mkdir ./build_web
cd ./build_web

emcmake cmake ..