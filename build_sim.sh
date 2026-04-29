#!/bin/bash
set -e

if [ -z "$CADMIUM" ]; then
    echo "ERROR: CADMIUM environment variable is not set."
    echo "Run: export CADMIUM=~/cadmium_v2/include"
    exit 1
fi

mkdir -p build bin output
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cd ..
echo "Build complete."
echo "Run: ./bin/UAVSearch config/uav_config.json 200"