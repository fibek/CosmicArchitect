#include "Timeline.hpp"
#include <fstream>

void Timeline::addMilestone(std::unique_ptr<Milestone> milestone) {
    milestones.push_back(std::move(milestone));
}

void Timeline::clear() {
    milestones.clear();
}

const std::vector<std::unique_ptr<Milestone>>& Timeline::getMilestones() const {
    return milestones;
}

nlohmann::json Timeline::toJson() const {
    nlohmann::json j;
    j["milestones"] = nlohmann::json::array();
    for (const auto& milestone : milestones) {
        j["milestones"].push_back(milestone->toJson());
    }
    return j;
}

bool Timeline::saveToFile(const std::string& filename) const {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        file << toJson().dump(4);
        return true;
    } catch (...) {
        return false;
    }
} 