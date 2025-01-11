#include "Universe.hpp"
#include <cmath>

// Initialize static member
int Universe::totalUniverses = 0;

Universe::Universe(double matterDensity,
                  double darkEnergyDensity,
                  double hubbleConstant,
                  double matterAntimatterRatio,
                  double darkEnergyW)
    : matterDensity(matterDensity)
    , darkEnergyDensity(darkEnergyDensity)
    , hubbleConstant(hubbleConstant)
    , matterAntimatterRatio(matterAntimatterRatio)
    , darkEnergyW(darkEnergyW) {
    // Calculate derived parameters
    curvatureParameter = 1.0 - (matterDensity + darkEnergyDensity);
    ++totalUniverses;
}

int Universe::getTotalUniverses() {
    return totalUniverses;
}

bool Universe::willUndergoAcceleration() const {
    // Universe accelerates if dark energy density is positive
    return darkEnergyDensity > 0;
}

bool Universe::willUndergoRip() const {
    // Big Rip occurs if dark energy has phantom behavior (w < -1)
    return darkEnergyDensity > 0 && darkEnergyW < -1;
}

bool Universe::willUndergoCollapse() const {
    // Universe collapses if total energy density > 1 (closed universe)
    // or if dark energy is negative
    return (matterDensity + darkEnergyDensity > 1) || darkEnergyDensity < 0;
}

double Universe::calculateRipTime() const {
    if (!willUndergoRip()) {
        return std::numeric_limits<double>::infinity();
    }

    // Approximate time to Big Rip in Gyr
    // t_rip ≈ t_0 + 2/(3|1+w|H_0)
    const double currentTime = 13.8; // Current age of universe in Gyr
    const double H0_in_Gyr = hubbleConstant * 0.001 * SECONDS_PER_YEAR * BILLION; // Convert to Gyr^-1
    return currentTime + 2.0 / (3.0 * std::abs(1.0 + darkEnergyW) * H0_in_Gyr);
} 