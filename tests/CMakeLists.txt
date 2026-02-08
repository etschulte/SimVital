project(SimVitalTests)

# Find test framework
find_package(Qt6 REQUIRED COMPONENTS Test)

# Add executable
add_executable(SimVitalTests
    tst_Waveform.cpp
)

# Link core with tests
target_link_libraries(SimVitalTests PRIVATE
    SimVitalCore
    Qt6::Test
)

# Register with CTest
add_test(NAME WaveformTest COMMAND SimVitalTests)