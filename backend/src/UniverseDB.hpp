#pragma once

#include "SimulatedUniverse.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <atomic>
#include <string_view>
#include <optional>

class UniverseDB {
public:
    // Singleton access
    static UniverseDB& instance() {
        static UniverseDB instance;
        return instance;
    }

    // Delete copy/move operations to ensure singleton pattern
    UniverseDB(const UniverseDB&) = delete;
    UniverseDB& operator=(const UniverseDB&) = delete;
    UniverseDB(UniverseDB&&) = delete;
    UniverseDB& operator=(UniverseDB&&) = delete;

    // Core operations
    int addUniverse(std::unique_ptr<SimulatedUniverse> universe);
    std::optional<std::reference_wrapper<SimulatedUniverse>> getUniverse(int id);
    std::vector<std::reference_wrapper<SimulatedUniverse>> getAllUniverses();
    std::vector<std::reference_wrapper<SimulatedUniverse>> searchUniverses(std::string_view term);
    bool removeUniverse(int id);
    size_t getUniverseCount() const;

    // Export methods
    std::optional<std::string> exportToJSON(int id) const;
    std::optional<std::string> exportToCSV(int id) const;

private:
    UniverseDB() = default;  // Private constructor for singleton

    std::vector<std::unique_ptr<SimulatedUniverse>> universes;
    mutable std::mutex universes_mutex;
    std::atomic<int> next_id{0};
}; 