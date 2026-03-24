# UAV Search Path Planning -- Cell-DEVS Simulation

**SYSC 5104 -- Assignment 2**  
Rachid Fahmi · 101415381 · Carleton University · Winter 2026

---

## Overview

This project implements a **Cell-DEVS model** of UAV search path planning on a **30×30 grid** using **Cadmium v2**.

Each cell stores two values:

| Field  | Type     | Meaning                      |
|--------|----------|------------------------------|
| `prob` | `double` | Target probability in [0, 1] |
| `uav`  | `int`    | `0` = empty, `100` = UAV     |

The two conceptual layers from the formal specification (UAV layer and probability layer) are merged into a **single cell state** to preserve Cell-DEVS locality and avoid explicit cross-layer coupling.

---

## Model Behavior

### Probability Diffusion

Every cell updates its `prob` value at each step using a **Moore neighborhood** (8 neighbors):

```text
P_new = (1 - 8a) * P_self + a * sum(P_neighbors)
```

> **Important:** Stability requires `a < 0.125`. The default value is `a = 0.05`.

### UAV Movement

The UAV always moves to the neighboring cell with the highest probability.

Ties are broken clockwise starting from North:

N → NE → E → SE → S → SW → W → NW

Exactly one cell holds `uav = 100` at all times.

---

## Project Structure

```
UAVSearchPath/
├── CMakeLists.txt
├── build_sim.sh
├── config/
│   └── uav_config.json
├── main/
│   ├── main.cpp
│   └── include/
│       ├── uav_search_state.hpp
│       └── uav_search_cell.hpp
├── output/
│   └── uav_log.csv
└── videos/
    └── UAV SAR CELL DEVS.webm
```

---

## Prerequisites

- Cadmium v2
- CMake 3.14 or newer
- `g++` with C++17 support

Cadmium header paths are configured in `CMakeLists.txt`.

---

## Build and Run

1. Build:

```bash
./build_sim.sh
```

2. Run full simulation:

```bash
./bin/UAVSearch config/uav_config.json 200
```

Output is written to:

- `output/uav_log.csv`

---

## Visualizing Results

Open the Cell-DEVS Web Viewer and upload:

- `config/uav_config.json`
- `output/uav_log.csv`

### Viewer Requirements

- `origin` must be `[0, 0]` in the JSON file
- The JSON file must contain a `viewer` section with `prob` and `uav` layers
- Cell state must be printed as `prob,uav` with no spaces
- The CSV file must be semicolon-separated

> **Note:** The viewer expects GitHub-friendly plain text formatting in the exported state values, so avoid adding spaces inside `prob,uav`.

---

## Experiments

| # | UAV Start | Hotspot | What to Observe |
|---|-----------|---------|-----------------|
| 1 | (0, 0) | (22, 22) | UAV follows the diffused gradient |
| 2 | (0, 0) | (22, 22) | Probability-only ring expands outward |

---

## Known Behavior

Near the target region, the UAV may oscillate between a small group of neighboring cells. This happens because:

- the probability field flattens due to diffusion
- the movement rule is purely local
- there is no stopping condition
- there is no revisit penalty

> **Tip:** This is an expected limitation of local hill-climbing on a dynamic field, not a bug.
