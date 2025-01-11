#pragma once

#include "Universe.hpp"
#include "Timeline.hpp"
#include <memory>

class SimulatedUniverse : public Universe {
public:
    SimulatedUniverse(double matterDensity = 0.3,      // Ω_m
                     double darkEnergyDensity = 0.7,   // Ω_Λ
                     double hubbleConstant = 70.0,     // H_0
                     double matterAntimatterRatio = 1e-9,
                     double darkEnergyW = -1.0);       // w

    // Implementation of pure virtual method
    std::unique_ptr<Timeline> generateTimeline() override;

private:
    // Helper methods for milestone creation
    std::unique_ptr<Milestone> createMilestone(MilestoneType type, const UniverseParameters& params) const;
    std::string selectAssetForMilestone(MilestoneType type) const;
}; 