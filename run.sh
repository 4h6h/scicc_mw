#!/bin/bash

IMAGE='rastac'

CONT_NAME='cross'
CONT_WD='app'
CONT_VOLUME='.'

EXEC_DIR='build/exec/bin'

# run the cross-compilation process within a docker container
docker container run --rm -p 8888:8888 -v .:/${CONT_WD} -w /${CONT_WD} --name ${CONT_NAME} ${IMAGE} /${CONT_WD}/${EXEC_DIR}/sci_cc_comp
