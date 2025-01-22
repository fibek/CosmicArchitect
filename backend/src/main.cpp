#include <iostream>
#include "SimulatedUniverse.hpp"

int main() {
    try {
        // Create a universe with some initial parameters
        SimulatedUniverse universe(
            1.0,    // initialEnergyDensity
            0.27,   // darkMatterRatio (27% of the universe)
            0.68,   // darkEnergyDensity (68% of the universe)
            67.4,   // expansionRate (Hubble constant in km/s/Mpc)
            1e-10   // matterAntimatterRatio
        );

        // Generate timeline
        auto timeline = universe.generateTimeline();

        // Save to JSON file
        if (timeline->saveToFile("universe_timeline.json")) {
            std::cout << "Timeline saved successfully!\n";
        } else {
            std::cerr << "Failed to save timeline.\n";
            return 1;
        }

        // Print some basic stats
        std::cout << "Total milestones generated: " 
                  << timeline->getMilestones().size() << "\n";
        std::cout << "Total universes created: " 
                  << Universe::getTotalUniverses() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
} 