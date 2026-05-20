#!/bin/bash

BBNET_DIR="bbnet"
BUILD_DIR="build"
SOURCE_DIR="."

if [ -d "$BBNET_DIR" ]; then
    rm -rf "$BBNET_DIR"
fi

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi
git clone https://github.com/ncc1700/brickbox-net.git bbnet
mkdir "$BUILD_DIR"
cmake -S "$SOURCE_DIR" -B "$BUILD_DIR"
echo now go to the \""$BUILD_DIR"\" directory and build it there