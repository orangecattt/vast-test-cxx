#!/bin/zsh

# load config
source config

# pull the latest commit
git fetch &> /dev/null
git pull &> /dev/null

# config and run test
BUILD_DIR="build"
if [[ ! -d ${BUILD_DIR} ]]; then
    mkdir ${BUILD_DIR}
fi
cd ${BUILD_DIR}

cmake .. -DVAST_PATH=${VAST_PATH} -DLIT_PATH=${LIT_PATH} &> /dev/null

ctest &> /dev/null

cd ..

# collect test result
./collect.py
