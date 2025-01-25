#include "Universe.hpp"
#include <cmath>

// Initialize static member
int Universe::totalUniverses = 0;

Universe::Universe(double matterDensity,
                  double darkEnergyDensity,
                  double hubbleConstant,
                  double matterAntimatterRatio,
                  double darkEnergyW,
                  std::string name)
    : matterDensity(matterDensity)
    , darkEnergyDensity(darkEnergyDensity)
    , hubbleConstant(hubbleConstant)
    , matterAntimatterRatio(matterAntimatterRatio)
    , darkEnergyW(darkEnergyW)
    , name(std::move(name))
{
    // Calculate derived parameters
    curvatureParameter = 1.0 - (matterDensity + darkEnergyDensity);
    ++totalUniverses;
}

int Universe::getTotalUniverses() {
    return totalUniverses;
}

bool Universe::willUndergoAcceleration() const {
    // Universe will accelerate if dark energy dominates over matter
    return darkEnergyDensity > 0 && darkEnergyW < -1.0/3.0;
}

bool Universe::willUndergoRip() const {
    // Big Rip occurs in phantom energy scenarios where w < -1
    return darkEnergyDensity > 0 && darkEnergyW < -1.0;
}

bool Universe::willUndergoCollapse() const {
    // Universe will collapse if total density > 1 and dark energy isn't dominant
    return (matterDensity + darkEnergyDensity > 1.0) && 
           (matterDensity > darkEnergyDensity || darkEnergyW > -1.0);
}

double Universe::calculateRipTime() const {
    if (!willUndergoRip()) {
        return -1.0; // No rip occurs
    }
    
    // Approximate time to Big Rip in billions of years
    // Based on current Hubble time and dark energy parameters
    double H0_Gyr = hubbleConstant / (SECONDS_PER_YEAR * BILLION); // Convert to Gyr^-1
    double t_rip = 2.0 / (3.0 * std::abs(darkEnergyW + 1.0) * H0_Gyr * std::sqrt(darkEnergyDensity));
    return t_rip;
} 