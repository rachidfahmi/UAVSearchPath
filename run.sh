#!/bin/bash
set -e
mkdir -p output

# Guard: ensure binary exists
if [ ! -f ./bin/UAVSearch ]; then
    echo "ERROR: Binary not found. Run: bash build_sim.sh first."
    exit 1
fi

echo "=== Scenario 1: UAV at (0,0), hotspot at (22,22), alpha=0.05 ==="
./bin/UAVSearch config/uav_config.json 200
tail -n +2 output/uav_log.csv | sed 's/$/\r/' > output/scenario1_uav_log.csv
echo "Output: output/scenario1_uav_log.csv"

echo ""
echo "=== Scenario 2: UAV at (15,15), hotspot at (5,5), alpha=0.08 ==="
./bin/UAVSearch config/uav_config_scenario2.json 200
tail -n +2 output/uav_log.csv | sed 's/$/\r/' > output/scenario2_uav_log.csv
echo "Output: output/scenario2_uav_log.csv"

echo ""
echo "Done. Visualize at: https://devssim.carleton.ca/cell-devs-viewer/"