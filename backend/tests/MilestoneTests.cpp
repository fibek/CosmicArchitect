#include <gtest/gtest.h>
#include "../src/MilestoneTypes.hpp"
#include "../src/UniverseParameters.hpp"
#include <vector>
#include <string>
#include <cmath>

// Helper struct to represent a milestone timing test case
struct MilestoneTimingTest {
    std::string name;
    double timestampGyr;
    MilestoneType type;
};

// Helper struct to represent a universe test scenario
struct UniverseScenario {
    std::string name;
    UniverseParameters params;
    std::vector<MilestoneTimingTest> expectedMilestones;
};

// Helper function to check if two timestamps are approximately equal
bool isTimestampEqual(double expected, double actual) {
    // Special cases for invalid timestamps (-1)
    if (expected < 0 || actual < 0) {
        return (expected < 0) == (actual < 0);
    }
    
    // Special case for Big Bang (exactly 0)
    if (expected == 0.0 && actual == 0.0) {
        return true;
    }
    
    // Handle infinity and heat death cases
    if (std::isinf(actual) || expected > 1e50) {
        return (std::isinf(actual) && expected > 1e50) || 
               (std::isinf(expected) && actual > 1e50) ||
               (expected == 1e100 && actual == 1e100);
    }
    
    // For very early universe events (before 1e-20 Gyr)
    if (expected < 1e-20) {
        return std::abs(std::log10(actual) - std::log10(expected)) < 2.0;
    }
    
    // For early universe events (before 1e-10 Gyr)
    if (expected < 1e-10) {
        return std::abs(std::log10(actual) - std::log10(expected)) < 1.5;
    }
    
    // For events before 1 Gyr
    if (expected < 1.0) {
        return std::abs(actual - expected) / expected < 1.0;
    }
    
    // For later events
    return std::abs(actual - expected) / expected < 0.5;
}

// Test scenarios
std::vector<UniverseScenario> getTestScenarios() {
    std::vector<UniverseScenario> scenarios;

    // Scenario 1: Baryon-Only Universe
    {
        UniverseParameters params;
        params.setInitialEnergyDensity(1.0);
        params.setDarkMatterRatio(0.0);
        params.setDarkEnergyDensity(0.5);
        params.setHubbleConstant(60.0);
        params.setMatterAntimatterRatio(1e-7);
        params.setDarkEnergyW(-1.0);

        std::vector<MilestoneTimingTest> milestones = {
            {"Big Bang", 0.0, MilestoneType::BigBang},
            {"Inflation", 1.0e-49, MilestoneType::Inflation},
            {"Nucleosynthesis", 1.0e-14, MilestoneType::NucleosynthesisBBN},
            {"Recombination", 0.001, MilestoneType::Recombination},
            {"Dark Ages", 0.001, MilestoneType::DarkAges},
            {"First Stars", 0.3, MilestoneType::FirstStars},
            {"Galaxy Formation", 1.0, MilestoneType::GalaxyFormation},
            {"Acceleration", 6.0, MilestoneType::AcceleratedExpansion},
            {"Heat Death", 1.0e100, MilestoneType::HeatDeath}
        };

        scenarios.push_back({"Baryon-Only Universe", params, milestones});
    }

    // Scenario 2: Matter-Dominated Universe
    {
        UniverseParameters params;
        params.setInitialEnergyDensity(2.0);
        params.setDarkMatterRatio(0.95);
        params.setDarkEnergyDensity(0.0);
        params.setHubbleConstant(55.0);
        params.setMatterAntimatterRatio(1e-9);
        params.setDarkEnergyW(0.0);

        std::vector<MilestoneTimingTest> milestones = {
            {"Big Bang", 0.0, MilestoneType::BigBang},
            {"Inflation", 1.0e-49, MilestoneType::Inflation},
            {"Particle Era", 1.0e-23, MilestoneType::ParticleEra},
            {"Nucleosynthesis", 1.0e-13, MilestoneType::NucleosynthesisBBN},
            {"Recombination", 0.0004, MilestoneType::Recombination},
            {"Dark Ages", 0.0004, MilestoneType::DarkAges},
            {"First Stars", 0.07, MilestoneType::FirstStars},
            {"Galaxy Formation", 0.3, MilestoneType::GalaxyFormation},
            {"Big Crunch", 50.0, MilestoneType::BigCrunch}
        };

        scenarios.push_back({"Matter-Dominated Universe", params, milestones});
    }

    // Scenario 3: Phantom Energy Universe
    {
        UniverseParameters params;
        params.setInitialEnergyDensity(1.0);
        params.setDarkMatterRatio(0.2);
        params.setDarkEnergyDensity(0.8);
        params.setHubbleConstant(70.0);
        params.setMatterAntimatterRatio(1e-9);
        params.setDarkEnergyW(-1.2);

        std::vector<MilestoneTimingTest> milestones = {
            {"Big Bang", 0.0, MilestoneType::BigBang},
            {"Inflation", 1.0e-49, MilestoneType::Inflation},
            {"Nucleosynthesis", 1.0e-12, MilestoneType::NucleosynthesisBBN},
            {"Recombination", 0.00038, MilestoneType::Recombination},
            {"Dark Ages", 0.00038, MilestoneType::DarkAges},
            {"First Stars", 0.15, MilestoneType::FirstStars},
            {"Galaxy Formation", 0.5, MilestoneType::GalaxyFormation},
            {"Acceleration", 3.0, MilestoneType::AcceleratedExpansion},
            {"Big Rip", 20.0, MilestoneType::BigRip}
        };

        scenarios.push_back({"Phantom Energy Universe", params, milestones});
    }

    // Scenario 4: Radiation-Baryon Universe
    {
        UniverseParameters params;
        params.setInitialEnergyDensity(1.5);
        params.setDarkMatterRatio(0.0);
        params.setDarkEnergyDensity(0.0);
        params.setHubbleConstant(80.0);
        params.setMatterAntimatterRatio(1e-8);
        params.setDarkEnergyW(0.0);

        std::vector<MilestoneTimingTest> milestones = {
            {"Big Bang", 0.0, MilestoneType::BigBang},
            {"Inflation", 1.0e-49, MilestoneType::Inflation},
            {"Particle Era", 1.0e-21, MilestoneType::ParticleEra},
            {"Nucleosynthesis", 1.0e-13, MilestoneType::NucleosynthesisBBN},
            {"Recombination", 0.002, MilestoneType::Recombination},
            {"Dark Ages", 0.002, MilestoneType::DarkAges},
            {"First Stars", 0.5, MilestoneType::FirstStars},
            {"Galaxy Formation", 2.0, MilestoneType::GalaxyFormation},
            {"Heat Death", 1.0e100, MilestoneType::HeatDeath}
        };

        scenarios.push_back({"Radiation-Baryon Universe", params, milestones});
    }

    // Scenario 5: Extreme Baryon Asymmetry
    {
        UniverseParameters params;
        params.setInitialEnergyDensity(1.0);
        params.setDarkMatterRatio(0.7);
        params.setDarkEnergyDensity(0.3);
        params.setHubbleConstant(70.0);
        params.setMatterAntimatterRatio(1e-20);
        params.setDarkEnergyW(-1.0);

        std::vector<MilestoneTimingTest> milestones = {
            {"Big Bang", 0.0, MilestoneType::BigBang},
            {"Inflation", 1.0e-49, MilestoneType::Inflation},
            {"Nucleosynthesis", 1.0e-12, MilestoneType::NucleosynthesisBBN},
            {"Recombination", 0.00038, MilestoneType::Recombination},
            {"Dark Ages", 0.00038, MilestoneType::DarkAges},
            {"First Stars", -1.0, MilestoneType::FirstStars},
            {"Galaxy Formation", -1.0, MilestoneType::GalaxyFormation},
            {"Acceleration", 6.0, MilestoneType::AcceleratedExpansion},
            {"Heat Death", 1.0e100, MilestoneType::HeatDeath}
        };

        scenarios.push_back({"Baryon-Poor Universe", params, milestones});
    }

    return scenarios;
}

// Test suite
class MilestoneScenarioTest : public ::testing::Test {
protected:
    void SetUp() override {
        scenarios = getTestScenarios();
    }

    std::vector<UniverseScenario> scenarios;
};

// Test each scenario
TEST_F(MilestoneScenarioTest, TestAllScenarios) {
    for (const auto& scenario : scenarios) {
        SCOPED_TRACE("Testing scenario: " + scenario.name);
        
        for (const auto& expected : scenario.expectedMilestones) {
            SCOPED_TRACE("Testing milestone: " + expected.name);
            
            auto milestone = createMilestone(expected.type, scenario.params);
            double actualTime = milestone->calculateTimestamp();
            
            EXPECT_TRUE(isTimestampEqual(expected.timestampGyr, actualTime))
                << "Expected: " << expected.timestampGyr 
                << ", Got: " << actualTime;
        }
    }
}

// Test specific edge cases
TEST_F(MilestoneScenarioTest, TestBigRipConditions) {
    UniverseParameters params;
    params.setDarkEnergyW(-0.9); // w > -1
    params.setDarkEnergyDensity(0.7);
    
    auto milestone = createMilestone(MilestoneType::BigRip, params);
    EXPECT_LT(milestone->calculateTimestamp(), 0) 
        << "Big Rip should not occur when w > -1";
}

TEST_F(MilestoneScenarioTest, TestBigCrunchConditions) {
    UniverseParameters params;
    params.setDarkEnergyDensity(0.7);
    params.setMatterDensity(0.2);
    
    auto milestone = createMilestone(MilestoneType::BigCrunch, params);
    EXPECT_LT(milestone->calculateTimestamp(), 0) 
        << "Big Crunch should not occur in flat universe with dark energy";
}

TEST_F(MilestoneScenarioTest, TestStarFormationThreshold) {
    UniverseParameters params;
    params.setMatterAntimatterRatio(1e-16); // Below threshold
    
    auto milestone = createMilestone(MilestoneType::FirstStars, params);
    EXPECT_LT(milestone->calculateTimestamp(), 0) 
        << "Stars should not form with extremely low baryon density";
} 