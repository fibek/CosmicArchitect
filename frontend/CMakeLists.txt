# Create frontend executable
add_executable(cosmic_architect_ui src/main.cpp)

# Add dependencies
add_dependencies(cosmic_architect_ui cosmic_core)

# Add include directories
target_include_directories(cosmic_architect_ui 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/webui/include
    ${CMAKE_SOURCE_DIR}/backend/src
)

# Add library directories
target_link_directories(cosmic_architect_ui 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/webui/lib
)

# Link libraries
target_link_libraries(cosmic_architect_ui 
    PRIVATE 
    webui
    cosmic_core
    nlohmann_json::nlohmann_json
    pthread
) 