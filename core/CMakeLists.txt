project(SimVitalCore)

# Create the library
add_library(SimVitalCore STATIC
    src/PatientData.cpp
    src/WaveformGenerator.cpp
)

# Tells any app using this library to look in include folder for headers
target_include_directories(SimVitalCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Qt6 REQUIRED COMPONENTS Core) # Gets desired package
target_link_libraries(SimVitalCore PRIVATE Qt6::Core) #connects it to SimVitalCore library