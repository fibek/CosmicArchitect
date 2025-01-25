#ifndef SIMULATED_UNIVERSE_HPP
#define SIMULATED_UNIVERSE_HPP

#include "Universe.hpp"
#include "Timeline.hpp"
#include <memory>
#include <string>

class SimulatedUniverse : public Universe {
public:
    SimulatedUniverse(std::string name, double matterDensity, double darkEnergyDensity, 
                     double hubbleConstant, double matterAntimatterRatio, double darkEnergyW);

    // Implementation of pure virtual method
    std::unique_ptr<Timeline> generateTimeline() override;

private:
    // Helper methods for milestone creation
    std::unique_ptr<Milestone> createMilestone(MilestoneType type, const UniverseParameters& params) const;
    std::string selectAssetForMilestone(MilestoneType type) const;

    bool willUndergoAcceleration() const {
        return darkEnergyDensity > 0;
    }
    
    bool willUndergoRip() const {
        return darkEnergyW < -1;
    }
    
    bool willUndergoCollapse() const {
        return matterDensity > 1.0 && darkEnergyDensity < 0.7;
    }
    
    double calculateRipTime() const {
        if (!willUndergoRip()) return -1;
        return 2.0 / (3.0 * std::abs(1.0 + darkEnergyW) * hubbleConstant);
    }
};

#endif 