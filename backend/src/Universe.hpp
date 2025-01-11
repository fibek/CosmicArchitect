#pragma once

#include <memory>
#include <string>
#include "Timeline.hpp"

class Universe {
public:
    Universe(double matterDensity,      // Ω_m (total matter density)
            double darkEnergyDensity,   // Ω_Λ (dark energy density)
            double hubbleConstant,      // H_0 in km/s/Mpc
            double matterAntimatterRatio, // typically 10^-9 to 10^-10
            double darkEnergyW = -1.0); // w parameter, -1 for standard ΛCDM
    
    virtual ~Universe() = default;

    // Pure virtual method for timeline generation
    virtual std::unique_ptr<Timeline> generateTimeline() = 0;

    // Static methods for universe tracking
    static int getTotalUniverses();

protected:
    // Core cosmological parameters
    double matterDensity;       // Ω_m
    double darkEnergyDensity;   // Ω_Λ
    double hubbleConstant;      // H_0
    double matterAntimatterRatio;
    double darkEnergyW;         // Equation of state parameter

    // Derived parameters
    double curvatureParameter;  // Ω_k = 1 - (Ω_m + Ω_Λ)

    // Helper methods for universe fate calculation
    bool willUndergoAcceleration() const;
    bool willUndergoRip() const;
    bool willUndergoCollapse() const;
    double calculateRipTime() const;  // Returns time in Gyr if Big Rip occurs

    // Time conversion constants
    static constexpr double SECONDS_PER_YEAR = 365.25 * 24 * 60 * 60;
    static constexpr double BILLION = 1e9;

private:
    static int totalUniverses;
}; 