#pragma once

#include <vector>
#include <memory>
#include "Milestone.hpp"

class Timeline {
public:
    Timeline() = default;
    
    void addMilestone(std::unique_ptr<Milestone> milestone);
    void clear();
    
    // Get milestones
    const std::vector<std::unique_ptr<Milestone>>& getMilestones() const;
    
    // Export timeline to JSON
    nlohmann::json toJson() const;
    
    // Save timeline to file
    bool saveToFile(const std::string& filename) const;

private:
    std::vector<std::unique_ptr<Milestone>> milestones;
}; 