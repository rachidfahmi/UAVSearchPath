#!/bin/bash
set -e
mkdir -p output

echo "=== Scenario 1: UAV at (0,0), hotspot at (22,22), alpha=0.05, 200 steps ==="
./bin/UAVSearch config/uav_config.json 200
cp output/uav_log.csv output/scenario1_uav_log.csv
echo "Output: output/scenario1_uav_log.csv"

echo ""
echo "=== Scenario 2: UAV at (15,15), hotspot at (5,5), alpha=0.08, 200 steps ==="
./bin/UAVSearch config/uav_config_scenario2.json 200
cp output/uav_log.csv output/scenario2_uav_log.csv
echo "Output: output/scenario2_uav_log.csv"

echo ""
echo "Done. Visualize at: https://devssim.carleton.ca/cell-devs-viewer/"
