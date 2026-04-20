#!/bin/bash
set -e

mkdir -p output

echo "Running UAV Search Path Planning simulation..."
echo "Command: ./bin/UAVSearch config/uav_config.json 200"

./bin/UAVSearch config/uav_config.json 200

echo
echo "Simulation completed successfully."
echo "Output file: output/uav_log.csv"
echo
echo "Preview of log file:"
head -n 20 output/uav_log.csv
