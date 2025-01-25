add_library(cosmic_core
    Universe.cpp
    SimulatedUniverse.cpp
    Timeline.cpp
    UniverseDB.cpp
)

target_link_libraries(cosmic_core PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(cosmic_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cosmic_architect main.cpp)
target_link_libraries(cosmic_architect PRIVATE cosmic_core) 