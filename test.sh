#!/bin/zsh

# chdir
cd "$(dirname "$(realpath "$0")")"

# load config
source config

# parse args
zparseopts -D - -vast-target:=vast_target
vast_target="${vast_target##*[= ]}"
if [[ -n ${vast_target} ]]; then
    VAST_TARGET=${vast_target}
fi

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
if [ -z ${TESTCASE} ]; then
    TESTCASE='.'
fi
if [ -z ${VAST_TARGET} ]; then
    VAST_TARGET='hl'
fi

cmake .. -DVAST_PATH=${VAST_PATH} -DLIT_PATH=${LIT_PATH} -DLIT_BIN_NAME=${LIT_BIN_NAME} -DTESTCASE=${TESTCASE} -DVAST_TARGET=${VAST_TARGET} &> /dev/null

ctest &> /dev/null

cd ..

# collect test result
python3 collect.py $*
