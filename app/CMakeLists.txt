project(SimVitalApp)

# Create executable
add_executable(SimVitalApp
    main.cpp
)

# Gives access to SimVitalCore's headers
target_link_libraries(SimVitalApp PRIVATE 
    SimVitalCore
    Qt6::Quick
    Qt6:Sql
)