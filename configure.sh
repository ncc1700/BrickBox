#!/bin/bash

BUILD_DIR="build"
SOURCE_DIR="."

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"
cmake -S "$SOURCE_DIR" -B "$BUILD_DIR"
echo now go to the \""$BUILD_DIR"\" directory and build it there