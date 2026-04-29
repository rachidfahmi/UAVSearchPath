#!/bin/bash
set -e
mkdir -p output

echo "=== Scenario 1: UAV at (0,0), hotspot at (22,22), 200 steps ==="
./bin/UAVSearch config/uav_config.json 200
cp output/uav_log.csv output/scenario1_uav_log.csv

echo "=== Scenario 2: Same config, extended 500 steps ==="
./bin/UAVSearch config/uav_config.json 500
cp output/uav_log.csv output/scenario2_uav_log.csv

echo "Done. Visualize at: https://devssim.carleton.ca/cell-devs-viewer/"
