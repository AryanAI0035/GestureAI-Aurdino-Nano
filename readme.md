
# Edge AI Hand Gesture Recognition System

## Abstract

This repository contains the hardware schematic, data pipeline, and firmware for a localized, offline Hand Gesture Recognition system. The project demonstrates the deployment of a Machine Learning classification model directly onto bare-metal microcontroller hardware (Arduino Nano) utilizing the TinyML paradigm.

By employing a highly constrained spatial array of three Digital Infrared (IR) Proximity Sensors, the system detects temporal hand gestures and executes inference locally in under 20 milliseconds, utilizing less than 15% of the microcontroller's 30 KB Flash Memory.

## Demonstration

`![System Demonstration](assets/demo_video.MP4)`

## System Architecture

### Hardware Specifications

* **Microcontroller:** Arduino Nano (ATmega328P, 16 MHz, 32 KB Flash, 2 KB SRAM)
* **Input Peripherals:** 3x Digital IR Proximity Sensors
* **Output Peripherals:** 2x LEDs (Green, Red) acting as action indicators.
* **Architecture:** Offline Edge Inference (No cloud connectivity or external coprocessors).

### Pin Mapping

| Component | Microcontroller Pin | Function |
| --- | --- | --- |
| IR Sensor (Up) | D2 | Spatial Trigger (Y-Axis) |
| IR Sensor (Down) | D3 | Spatial Trigger (Y-Axis) |
| IR Sensor (Left) | D4 | Spatial Trigger (X-Axis) |
| Indicator LED 2 | D8 | Output: "Swipe Left" Gesture |
| Indicator LED 3 | D10 | Output: "Swipe Right" Gesture |

## Machine Learning Methodology

### 1. Data Acquisition

Data was captured physically by polling the raw binary states (1 or 0) of the sensor array at a 10Hz sampling rate and exporting via Serial communication. The classes recorded include `Swipe Left`, `Swipe Right`, `Push In`, and an `Idle` baseline.

### 2. Temporal Feature Engineering

To capture the trajectory of movement rather than static states, the system implements Time-Series Windowing. The continuous data stream is chunked into overlapping windows of 8 frames (representing 0.8 seconds of motion). This results in a flattened 24-feature vector (8 frames x 3 sensors) passed to the inference engine per cycle.

### 3. Model Optimization and Compilation

The initial model was trained in Python using Scikit-Learn. To facilitate edge deployment, the model was pruned to respect the strict memory limitations of the ATmega328P. The optimized weights and logic structure were then cross-compiled into a static C++ header file (`GestureModel.h`) using the `micromlgen` library.

## Performance Analysis and Trade-offs

A core challenge of TinyML is balancing model complexity with extreme hardware limitations. Below is the comparative analysis of the architectures tested during the development lifecycle:

| Metric | Random Forest (20 Estimators) | Decision Tree (Max Depth = 6) |
| --- | --- | --- |
| **Validation Accuracy** | ~94.4% | ~91.5% |
| **Flash Memory Allocation** | 42,794 Bytes | ~4,600 Bytes |
| **Flash Utilization** | 139% (Overflow Failure) | ~15% (Success) |
| **SRAM Utilization** | > 2 KB (Heap Crash Risk) | < 450 Bytes |
| **Inference Latency** | ~120 ms | < 20 ms |

Switching from a Random Forest ensemble to a constrained Decision Tree reduced the memory footprint by approximately 90% while incurring only a nominal 3% accuracy penalty, allowing stable bare-metal execution.

## Engineering Challenges and Optimizations

1. **Temporal Overlap (Ghost Triggers):** Continuous polling of a sliding window introduces leftover fragmented data as a physical gesture completes and exits the sensor array. This resulted in false-positive sequential triggers.
* **Solution:** Implemented a synchronous "Snap and Clear" memory flush. Upon successful classification, the firmware halts polling, executes the output, and overwrites the 24-point feature buffer with baseline idle states.


2. **Premature Inference:** Non-uniform human hand geometry caused asymmetrical sensor triggering. The leading edge of a "Push In" gesture would frequently trigger the left sensor early, causing the model to misclassify the movement as the beginning of a "Swipe Right" before the full data window populated.
* **Solution:** Engineered an asynchronous inference delay. Upon detecting a non-idle state transition, the engine suspends prediction for 300ms to allow the spatial array to fully populate before classifying the sequence.


3. **Compiler Toolchain Incompatibilities:** The generated C++ inference code utilized modern standard libraries (`<cstdarg>`, `<cmath>`) unsupported by the legacy AVR-GCC toolchain used by the Arduino Nano.
* **Solution:** Manually refactored the generated header dependencies to their AVR-compatible C-equivalents (`<stdarg.h>`, `<math.h>`).



## Repository Structure

```text
├── AI_Gesture_Control/
│   ├── AI_Gesture_Control.ino    # Main Arduino firmware execution script
│   └── GestureModel.h            # Compiled C++ inference model
├── Python_Training/
│   ├── dataset/
│   │   ├── idle.csv
│   │   ├── push_in.csv
│   │   ├── swipe_left.csv
│   │   └── swipe_right.csv
│   └── train_model.py            # Model training and C++ conversion script
├── assets/                       # Images, schematics, and demo video
└── README.md

```

## Reproduction Instructions

### Prerequisites

* Python 3.8 or higher
* Arduino IDE 2.x

### Step 1: Environment Setup

Clone the repository and install the required Python dependencies:

```bash
git clone https://github.com/YourUsername/YourRepoName.git
cd YourRepoName
pip install pandas numpy scikit-learn micromlgen

```

### Step 2: Model Training

Navigate to the training directory and execute the pipeline:

```bash
cd Python_Training
python train_model.py

```

This script reads the CSV datasets, trains the Decision Tree, and outputs an updated `GestureModel.h` file.

### Step 3: Firmware Flashing

1. Move the generated `GestureModel.h` into the `AI_Gesture_Control` directory.
2. Open `AI_Gesture_Control.ino` in the Arduino IDE.
3. Select "Arduino Nano" as the target board. (Note: Depending on the board manufacturer, you may need to select "ATmega328P (Old Bootloader)" under the Processor menu).
4. Compile and upload the firmware.
5. Open the Serial Monitor at 9600 baud to observe real-time inference data.




