#!/bin/bash

# Created by:   VPR
# Updated:      April 1st, 2025

# Updated by:   VPR
# Updated:      April 1st, 2025

set -o pipefail
set -o errexit
set -o nounset
set -o xtrace

ROOT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

DOCKER_FILE="Dockerfile"
DOCKER_IMAGE="overwatch-dev"
USER_MOD="$(id -u):$(id -g)"
WORK_DIR="$(grep WORKDIR ${DOCKER_FILE} | awk '{print $2}')"

# Builds docker image using root Dockerfile if it doesn't already exist
[[ $(docker image ls -a | grep "${DOCKER_IMAGE}") ]] || docker build -f "${DOCKER_FILE}" -t "${DOCKER_IMAGE}" .

# Creates a docker container for the build
docker run -u ${USER_MOD} -itv ${ROOT_DIR}:${WORK_DIR} "${DOCKER_IMAGE}" /bin/bash -c "cmake -B docker-build && cmake --build docker-build"
