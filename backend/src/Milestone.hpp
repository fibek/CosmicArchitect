#pragma once

#include <string>
#include <memory>
#include <nlohmann/json.hpp>
#include "UniverseParameters.hpp"

enum class MilestoneType {
    BigBang,
    Inflation,
    ParticleEra,
    NucleosynthesisBBN,
    Recombination,
    DarkAges,
    FirstStars,
    GalaxyFormation,
    AcceleratedExpansion,
    BigRip,
    HeatDeath,
    BigCrunch
};

class Milestone {
public:
    Milestone(const UniverseParameters& params)
        : params(params)
    {}

    virtual ~Milestone() = default;

    // Convert to JSON
    nlohmann::json toJson() const {
        nlohmann::json j;
        j["type"] = static_cast<int>(getType());
        j["timestamp"] = calculateTimestamp();
        j["description"] = getDescription();
        j["assetId"] = getAssetId(params);
        return j;
    }

    // Pure virtual methods that derived classes must implement
    virtual double calculateTimestamp() const = 0;
    virtual std::string getDescription() const = 0;
    virtual MilestoneType getType() const = 0;
    virtual std::string getAssetId(const UniverseParameters& params) const = 0;

protected:
    const UniverseParameters& params;
};

// Factory function to create milestones
std::unique_ptr<Milestone> createMilestone(MilestoneType type, const UniverseParameters& params); 