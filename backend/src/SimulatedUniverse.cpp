#include "SimulatedUniverse.hpp"
#include "MilestoneTypes.hpp"
#include <cmath>

SimulatedUniverse::SimulatedUniverse(double matterDensity,
                                   double darkEnergyDensity,
                                   double hubbleConstant,
                                   double matterAntimatterRatio,
                                   double darkEnergyW)
    : Universe(matterDensity,
              darkEnergyDensity,
              hubbleConstant,
              matterAntimatterRatio,
              darkEnergyW)
{}

std::unique_ptr<Timeline> SimulatedUniverse::generateTimeline() {
    auto timeline = std::make_unique<Timeline>();
    UniverseParameters params(matterDensity, darkEnergyDensity, hubbleConstant, 
                            matterAntimatterRatio, darkEnergyW);
    
    // Always add Big Bang
    timeline->addMilestone(createMilestone(MilestoneType::BigBang, params));
    
    // Always add Inflation
    timeline->addMilestone(createMilestone(MilestoneType::Inflation, params));
    
    // Always add Particle Era
    timeline->addMilestone(createMilestone(MilestoneType::ParticleEra, params));
    
    // Add Nucleosynthesis if matter-antimatter ratio is sufficient
    if (matterAntimatterRatio >= 1e-11) {
        timeline->addMilestone(createMilestone(MilestoneType::NucleosynthesisBBN, params));
    }
    
    // Always add Recombination
    timeline->addMilestone(createMilestone(MilestoneType::Recombination, params));
    
    // Always add Dark Ages
    timeline->addMilestone(createMilestone(MilestoneType::DarkAges, params));
    
    // Add First Stars if matter-antimatter ratio is sufficient
    if (matterAntimatterRatio >= 1e-11) {
        timeline->addMilestone(createMilestone(MilestoneType::FirstStars, params));
    }
    
    // Add Galaxy Formation if matter density is sufficient
    if (matterDensity >= 0.05) {
        timeline->addMilestone(createMilestone(MilestoneType::GalaxyFormation, params));
    }
    
    // Add Accelerated Expansion if dark energy is positive
    if (willUndergoAcceleration()) {
        timeline->addMilestone(createMilestone(MilestoneType::AcceleratedExpansion, params));
    }
    
    // Add final fate
    if (willUndergoRip()) {
        timeline->addMilestone(createMilestone(MilestoneType::BigRip, params));
    } else if (willUndergoCollapse()) {
        timeline->addMilestone(createMilestone(MilestoneType::BigCrunch, params));
    } else {
        timeline->addMilestone(createMilestone(MilestoneType::HeatDeath, params));
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