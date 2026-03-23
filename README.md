# UAV Search Path Planning — Cell-DEVS Simulation
SYSC 5104 — Assignment 2  
Rachid Fahmi (101415381)

## Overview
This project implements a Cell-DEVS model of UAV search path planning on a 30x30 grid.

Each cell stores two values:
- `prob`: target probability in that cell
- `uav`: UAV state
  - `0` = empty
  - `1..8` = temporary movement direction code
  - `100` = UAV present

The model combines:
- probability diffusion over a Moore neighborhood
- UAV movement toward the highest neighboring probability

## Model Behavior

### Probability Field
The probability value diffuses over time using a Moore neighborhood:
- each cell reads its 8 neighbors
- probability spreads outward from high-probability regions
- diffusion coefficient `alpha` must satisfy:

```text
UAV Movement

The UAV movement is implemented with local Cell-DEVS rules in three stages:

Decide
If a cell contains the UAV (uav = 100), it chooses the best direction based on neighboring probability values.
Arrive
An empty neighboring cell becomes the new UAV cell if a direction code points to it.
Clear
Old direction-code cells are reset to 0.

This avoids UAV duplication and preserves Cell-DEVS locality.

### Project Structure
UAVSearchPath/
├── CMakeLists.txt
├── build_sim.sh
├── README.md
├── bin/
├── build/
├── config/
│   ├── prob_scenario.json
│   └── uav_scenario.json
├── main/
│   ├── main.cpp
│   └── include/
│       ├── uav_search_state.hpp
│       └── uav_search_cell.hpp
└── output/
### Prerequisites
Cadmium v2 installed locally
CMake
g++ with C++17 support

This project assumes Cadmium headers are available through the paths defined in CMakeLists.txt.

Build
./build_sim.sh
Run
Probability-only test
./bin/UAVSearch config/prob_scenario.json 50
Full UAV search simulation
./bin/UAVSearch config/uav_scenario.json 100
Output

Simulation logs are written to:

output/prob_log.csv
output/uav_log.csv

These files can be used with the DEVS / Cell-DEVS Web Viewer.

Web Viewer Notes

For the viewer to work correctly:

scenario origin must be [0,0]
the scenario JSON must contain a viewer section
the CSV log must be semicolon-separated
the state output format must match what the viewer expects

The working simulation uses:

config/uav_scenario.json
output/uav_log.csv
Example Experiments
1. Single hotspot
UAV starts at (0,0)
hotspot at (22,22)
UAV follows the diffused probability gradient toward the target region
2. Probability-only diffusion
hotspot starts at one cell
probability spreads outward over time
center probability decreases as neighbors gain probability
Known Behavior

The UAV may oscillate near the target region after reaching the highest-probability area. This happens because:

the movement rule is local
the probability field keeps diffusing
the model does not include stop logic, memory, or visit penalties

This is an expected limitation of local hill-climbing in a changing field.

Author

Rachid Fahmi
SYSC 5104 — Winter 2026
