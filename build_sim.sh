#!/bin/bash
set -e

if [ -z "$CADMIUM" ]; then
    echo "ERROR: CADMIUM environment variable is not set."
    echo "Run: ./run.sh"
    exit 1
fi

mkdir -p build bin output
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cd ..
echo "Build complete."
echo "Run: ./run.sh"