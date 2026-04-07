project(SimVitalApp)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Sql Qml)

qt_policy(SET QTP0001 NEW)

# Create executable
add_executable(SimVitalApp
    main.cpp
    controllers/EcgController.hpp
    controllers/EcgController.cpp
    controllers/SpO2Controller.hpp
    controllers/SpO2Controller.cpp
    controllers/SpO2WaveController.hpp
    controllers/SpO2WaveController.cpp
    controllers/RrController.hpp
    controllers/RrController.cpp
    controllers/NibpController.hpp
    controllers/NibpController.cpp
    controllers/ScenarioController.hpp
    controllers/ScenarioController.cpp
    ../core/include/SpO2Generator.hpp
    ../core/include/SpO2WaveGenerator.hpp
    ../core/include/RrGenerator.hpp
    ../core/include/NibpGenerator.hpp
    managers/AudioManager.hpp
    managers/AudioManager.cpp
    
)

set_source_files_properties(qml/main.qml
    PROPERTIES
    QT_RESOURCE_ALIAS
    main.qml
)

qt_add_qml_module(SimVitalApp 
    URI SimVital 
    VERSION 1.0 
    QML_FILES
        qml/main.qml
        qml/ReadingsBox.qml
        qml/NibpBox.qml
        qml/NavBar.qml
        qml/NavButton.qml
        qml/MonitorScreen.qml
        qml/ControlPanelScreen.qml
        qml/LogoutScreen.qml
        qml/TrendsScreen.qml
        qml/PatientScreen.qml
        qml/ScenarioButton.qml
)

# Gives access to SimVitalCore's headers
target_link_libraries(SimVitalApp PRIVATE 
    SimVitalCore
    Qt6::Quick
    Qt6::Sql
    Qt6::Gui
    Qt6::Core
    Qt6::Qml
)