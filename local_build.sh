#!/bin/bash

IMAGE='rastac'

CONT_NAME='cross'
CONT_WD='app'
CONT_VOLUME='.'

BUILD_DIR='build'

rm -rf ${BUILD_DIR}

# run the cross-compilation process within a docker container
docker container run --rm -v .:/${CONT_WD} -w /${CONT_WD} --name ${CONT_NAME} ${IMAGE} /bin/bash -c /${CONT_WD}/build.sh
