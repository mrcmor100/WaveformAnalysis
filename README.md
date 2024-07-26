# Waveform Analysis Project

## Overview

The Waveform Analysis Project is designed to process and analyze waveform data from ROOT files. The project uses various fitting strategies to analyze waveforms, and it is structured to be easily extendable and maintainable.

## Features

- **Waveform Analysis**: Analyze waveforms from ROOT files using different fitting strategies.
- **Preprocessing**: Determine the appropriate fit strategy based on waveform characteristics.
- **Modular Design**: Easily extendable with additional fit strategies and preprocessing steps.

## Getting Started

### Prerequisites

- CMake 3.10 or higher
- ROOT (with RIO, Net, Hist, Tree, and RDataFrame components)

### Building the Project

1. Clone the repository:

    ```sh
    git clone <repository-url>
    cd WaveformAnalysis
    ```

2. Create a build directory and run CMake:

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

### Running the Application

After building the project, you can run the application using:

```sh
./WaveformAnalysis <input ROOT file> <input TTree name> <output ROOT file>
