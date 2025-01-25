#pragma once

#include <string>
#include <optional>

class UniverseValidator {
public:
    struct ValidationResult {
        bool isValid;
        std::string message;
    };

    static ValidationResult validateParameters(
        double matterDensity,
        double darkEnergyDensity,
        double hubbleConstant,
        double matterAntimatterRatio,
        double darkEnergyW
    ) {
        // Matter Density (Ω_m): 0.1-2.0
        if (matterDensity < 0.1 || matterDensity > 2.0) {
            return {false, "Matter density must be between 0.1 and 2.0"};
        }

        // Dark Energy Density (Ω_Λ): 0.0-1.0
        if (darkEnergyDensity < 0.0 || darkEnergyDensity > 1.0) {
            return {false, "Dark energy density must be between 0.0 and 1.0"};
        }

        // Hubble Constant (H₀): 50-80 km/s/Mpc
        if (hubbleConstant < 50.0 || hubbleConstant > 80.0) {
            return {false, "Hubble constant must be between 50 and 80 km/s/Mpc"};
        }

        // Matter/Antimatter Ratio: 1e-11 to 1e-7
        if (matterAntimatterRatio < 1e-11 || matterAntimatterRatio > 1e-7) {
            return {false, "Matter/antimatter ratio must be between 1e-11 and 1e-7"};
        }

        // Dark Energy w: -2.0 to -0.5
        if (darkEnergyW < -2.0 || darkEnergyW > -0.5) {
            return {false, "Dark energy w must be between -2.0 and -0.5"};
        }

        // Check total density (flat universe constraint)
        double totalDensity = matterDensity + darkEnergyDensity;
        if (std::abs(totalDensity - 1.0) > 0.1) {  // Allow 10% deviation from flat universe
            return {false, "Total density (matter + dark energy) should be approximately 1.0"};
        }

        return {true, "Parameters are valid"};
    }
}; 