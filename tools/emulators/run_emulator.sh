#!/bin/sh
set -eou pipefail

CONTAINER_NAME=kotlin-emulator
IMAGE_NAME=kotlin-emulator


docker ps -a | grep $CONTAINER_NAME > /dev/null \
  && docker stop $CONTAINER_NAME &>- \
  && docker rm $CONTAINER_NAME &>-

EMULATOR=$1
SYSROOT=$2
EXECUTABLE=$3

docker run -it \
  -v "$SYSROOT":/sysroot \
  -v "$PWD":/binaries \
  --env EMULATOR="$EMULATOR" \
  --env EXECUTABLE="$EXECUTABLE" \
  --name=$CONTAINER_NAME $IMAGE_NAME