project(SimVitalCore)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOGEN_VERBOSE ON)

add_library(SimVitalCore STATIC 
    src/SpO2Generator.cpp
    src/MitBihParser.cpp
    src/RingBuffer.cpp
    src/ScenarioManager.cpp
    src/SpO2WaveGenerator.cpp
    src/RrGenerator.cpp
    src/NibpGenerator.cpp
    src/SimulationEngine.cpp
)

target_include_directories(SimVitalCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/SimVitalCore_autogen/include
)

find_package(Qt6 REQUIRED COMPONENTS Core)

target_link_libraries(SimVitalCore PUBLIC Qt6::Core)