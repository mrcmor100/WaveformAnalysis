cmake_minimum_required(VERSION 3.10)
project(WaveformAnalysis)

set(CMAKE_CXX_STANDARD 17)

# Options for testing and coverage
option(BUILD_TESTS "Build tests" ON)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

# Load the ROOT module (adjust as necessary)
execute_process(COMMAND bash -c "/group/nps/cmorean/setup.sh")

# Find the ROOT package
find_package(ROOT REQUIRED ROOTVecOps)

# Include ROOT headers
include_directories(${ROOT_INCLUDE_DIRS})

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Calorimeter.cpp
    src/GaussianFitStrategy.cpp
    src/ExponentialFitStrategy.cpp
    src/WaveformFitContext.cpp
    src/WaveformPreprocessor.cpp
    src/WaveformAnalyzer.cpp
)

# Main executable
add_executable(WaveformAnalysis ${SOURCES})

# Link ROOT libraries
find_package(ROOT REQUIRED COMPONENTS RIO Net Hist Tree ROOTVecOps)
include_directories(${ROOT_INCLUDE_DIRS})
target_link_libraries(WaveformAnalysis ${ROOT_LIBRARIES})

# Build tests
#if(BUILD_TESTS)
#    enable_testing()
#    add_subdirectory(tests)
#endif()

# Enable coverage
#if(ENABLE_COVERAGE)
#    target_compile_options(WaveformAnalysis PRIVATE --coverage)
#    target_link_libraries(WaveformAnalysis PRIVATE --coverage)
#endif()
