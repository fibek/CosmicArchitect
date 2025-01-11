add_library(cosmic_core
    Universe.cpp
    SimulatedUniverse.cpp
    Timeline.cpp
)

target_link_libraries(cosmic_core PRIVATE nlohmann_json::nlohmann_json)

add_executable(cosmic_architect main.cpp)
target_link_libraries(cosmic_architect PRIVATE cosmic_core) 