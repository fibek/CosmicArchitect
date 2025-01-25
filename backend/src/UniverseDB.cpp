#include "UniverseDB.hpp"
#include <algorithm>

int UniverseDB::addUniverse(std::unique_ptr<SimulatedUniverse> universe) {
    std::lock_guard<std::mutex> lock(universes_mutex);
    int id = next_id++;
    universes.push_back(std::move(universe));
    return id;
}

std::optional<std::reference_wrapper<SimulatedUniverse>> UniverseDB::getUniverse(int id) {
    std::lock_guard<std::mutex> lock(universes_mutex);
    if (id >= 0 && id < static_cast<int>(universes.size()) && universes[id]) {
        return std::ref(*universes[id]);
    }
    return std::nullopt;
}

std::vector<std::reference_wrapper<SimulatedUniverse>> UniverseDB::getAllUniverses() {
    std::lock_guard<std::mutex> lock(universes_mutex);
    std::vector<std::reference_wrapper<SimulatedUniverse>> result;
    result.reserve(universes.size());
    
    for (const auto& universe : universes) {
        if (universe) {  // Check if the universe pointer is valid
            result.push_back(std::ref(*universe));
        }
    }
    return result;
}

std::vector<std::reference_wrapper<SimulatedUniverse>> UniverseDB::searchUniverses(std::string_view term) {
    std::lock_guard<std::mutex> lock(universes_mutex);
    std::vector<std::reference_wrapper<SimulatedUniverse>> result;
    
    for (size_t i = 0; i < universes.size(); ++i) {
        if (universes[i]) {  // Check if the universe pointer is valid
            // For now, we'll just return all universes since we don't have a name/search criteria yet
            // TODO: Implement actual search logic when universe naming is added
            result.push_back(std::ref(*universes[i]));
        }
    }
    return result;
}

bool UniverseDB::removeUniverse(int id) {
    std::lock_guard<std::mutex> lock(universes_mutex);
    if (id >= 0 && id < static_cast<int>(universes.size())) {
        universes[id].reset();  // Clear the unique_ptr
        return true;
    }
    return false;
}

size_t UniverseDB::getUniverseCount() const {
    std::lock_guard<std::mutex> lock(universes_mutex);
    return std::count_if(universes.begin(), universes.end(), 
                        [](const auto& u) { return u != nullptr; });
}

std::optional<std::string> UniverseDB::exportToJSON(int id) const {
    std::lock_guard<std::mutex> lock(universes_mutex);
    if (id >= 0 && id < static_cast<int>(universes.size()) && universes[id]) {
        return universes[id]->toJSON();
    }
    return std::nullopt;
}

std::optional<std::string> UniverseDB::exportToCSV(int id) const {
    std::lock_guard<std::mutex> lock(universes_mutex);
    if (id >= 0 && id < static_cast<int>(universes.size()) && universes[id]) {
        return universes[id]->toCSV();
    }
    return std::nullopt;
} 