add_executable(cosmic_architect_ui src/main.cpp)

# Add WebUI library
target_include_directories(cosmic_architect_ui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/webui/include)
target_link_directories(cosmic_architect_ui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/webui/lib)
target_link_libraries(cosmic_architect_ui PRIVATE webui) 