# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.10.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Mocking library
include(FetchContent)
FetchContent_Declare(
    gmock
    URL https://github.com/google/googlemock/archive/release-1.10.0.zip
)
FetchContent_MakeAvailable(gmock)

# Test executable
add_executable(TestWaveformAnalysis
    TestWaveformAnalyzer.cpp
    MockWaveformFitStrategy.cpp
)

# Link test libraries
target_link_libraries(TestWaveformAnalysis
    gtest_main
    gmock_main
    ${ROOT_LIBRARIES}
)

# Add tests
add_test(NAME TestWaveformAnalysis COMMAND TestWaveformAnalysis)

# Enable coverage
if(ENABLE_COVERAGE)
    target_compile_options(TestWaveformAnalysis PRIVATE --coverage)
    target_link_libraries(TestWaveformAnalysis PRIVATE --coverage)
endif()