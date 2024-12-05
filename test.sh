#!/bin/zsh
# chdir is required 
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

if [ -z ${LIT_BIN_NAME} ]; then
    LIT_BIN_NAME='lit'
fi
cmake .. -DVAST_PATH=${VAST_PATH} -DLIT_PATH=${LIT_PATH} -DLIT_BIN_NAME=${LIT_BIN_NAME} -DTESTCASE=${TESTCASE} &> /dev/null

ctest &> /dev/null

cd ..

# collect test result
./collect.py
