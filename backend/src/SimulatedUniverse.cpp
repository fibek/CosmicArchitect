#include "SimulatedUniverse.hpp"
#include "MilestoneTypes.hpp"
#include <memory>
#include <cmath>

SimulatedUniverse::SimulatedUniverse(std::string name, double matterDensity, double darkEnergyDensity, 
                                   double hubbleConstant, double matterAntimatterRatio, double darkEnergyW)
    : Universe(matterDensity, darkEnergyDensity, hubbleConstant, 
              matterAntimatterRatio, darkEnergyW, std::move(name)) {
}

std::unique_ptr<Timeline> SimulatedUniverse::generateTimeline() {
    auto timeline = std::make_unique<Timeline>();
    UniverseParameters params(matterDensity, darkEnergyDensity, hubbleConstant, 
                            matterAntimatterRatio, darkEnergyW);
    
    // Always add Big Bang at t=0
    timeline->addMilestone(createMilestone(MilestoneType::BigBang, params));
    
    // Early universe events
    timeline->addMilestone(createMilestone(MilestoneType::Inflation, params));
    timeline->addMilestone(createMilestone(MilestoneType::ParticleEra, params));
    timeline->addMilestone(createMilestone(MilestoneType::NucleosynthesisBBN, params));
    
    // Matter formation events
    timeline->addMilestone(createMilestone(MilestoneType::Recombination, params));
    timeline->addMilestone(createMilestone(MilestoneType::DarkAges, params));
    
    // Structure formation events (if conditions allow)
    if (matterDensity >= 0.1) {  // Minimum matter density for star formation
        timeline->addMilestone(createMilestone(MilestoneType::FirstStars, params));
        timeline->addMilestone(createMilestone(MilestoneType::GalaxyFormation, params));
    }
    
    // Future events based on universe parameters
    if (willUndergoAcceleration()) {
        timeline->addMilestone(createMilestone(MilestoneType::AcceleratedExpansion, params));
        
        if (willUndergoRip()) {
            // Universe ends in Big Rip
            double ripTime = calculateRipTime();
            if (ripTime > 0) {
                timeline->addMilestone(createMilestone(MilestoneType::BigRip, params));
            }
        } else {
            // Universe expands forever and ends in Heat Death
            timeline->addMilestone(createMilestone(MilestoneType::HeatDeath, params));
        }
    } else if (willUndergoCollapse()) {
        // Universe ends in Big Crunch
        timeline->addMilestone(createMilestone(MilestoneType::BigCrunch, params));
    }
    
    return timeline;
}

std::unique_ptr<Milestone> SimulatedUniverse::createMilestone(MilestoneType type, const UniverseParameters& params) const {
    return ::createMilestone(type, params);
}

std::string SimulatedUniverse::selectAssetForMilestone(MilestoneType type) const {
    switch (type) {
        case MilestoneType::BigBang:
            return "big_bang_01";
        case MilestoneType::Inflation:
            return "inflation_01";
        case MilestoneType::ParticleEra:
            return "particle_era_01";
        case MilestoneType::NucleosynthesisBBN:
            return "nucleosynthesis_01";
        case MilestoneType::Recombination:
            return "recombination_01";
        case MilestoneType::DarkAges:
            return "dark_ages_01";
        case MilestoneType::FirstStars:
            return "first_stars_01";
        case MilestoneType::GalaxyFormation:
            return "galaxy_formation_01";
        case MilestoneType::AcceleratedExpansion:
            return "acceleration_01";
        case MilestoneType::BigRip:
            return "big_rip_01";
        case MilestoneType::HeatDeath:
            return "heat_death_01";
        case MilestoneType::BigCrunch:
            return "big_crunch_01";
        default:
            return "default_01";
    }
} 