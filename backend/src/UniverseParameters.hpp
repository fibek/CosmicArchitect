#pragma once

class UniverseParameters {
public:
    // Default constructor with reasonable default values
    UniverseParameters()
        : matterDensity(0.3)
        , darkEnergyDensity(0.7)
        , hubbleConstant(70.0)
        , matterAntimatterRatio(1e-9)
        , darkEnergyW(-1.0)
        , darkMatterRatio(0.25)
        , initialEnergyDensity(1.0)
    {}

    // Existing constructor
    UniverseParameters(double matterDensity,      // Ω_m
                      double darkEnergyDensity,   // Ω_Λ
                      double hubbleConstant,      // H_0
                      double matterAntimatterRatio,
                      double darkEnergyW)         // w
        : matterDensity(matterDensity)
        , darkEnergyDensity(darkEnergyDensity)
        , hubbleConstant(hubbleConstant)
        , matterAntimatterRatio(matterAntimatterRatio)
        , darkEnergyW(darkEnergyW)
        , darkMatterRatio(0.25)
        , initialEnergyDensity(1.0)
    {}

    // Getters
    double getMatterDensity() const { return matterDensity; }
    double getDarkEnergyDensity() const { return darkEnergyDensity; }
    double getHubbleConstant() const { return hubbleConstant; }
    double getMatterAntimatterRatio() const { return matterAntimatterRatio; }
    double getDarkEnergyW() const { return darkEnergyW; }
    double getDarkMatterRatio() const { return darkMatterRatio; }
    double getInitialEnergyDensity() const { return initialEnergyDensity; }

    // Setters
    void setMatterDensity(double value) { matterDensity = value; }
    void setDarkEnergyDensity(double value) { darkEnergyDensity = value; }
    void setHubbleConstant(double value) { hubbleConstant = value; }
    void setMatterAntimatterRatio(double value) { matterAntimatterRatio = value; }
    void setDarkEnergyW(double value) { darkEnergyW = value; }
    void setDarkMatterRatio(double value) { darkMatterRatio = value; }
    void setInitialEnergyDensity(double value) { initialEnergyDensity = value; }

private:
    double matterDensity;        // Ω_m - density parameter for matter
    double darkEnergyDensity;    // Ω_Λ - density parameter for dark energy
    double hubbleConstant;       // H_0 - Hubble constant in km/s/Mpc
    double matterAntimatterRatio;// η - baryon-to-photon ratio
    double darkEnergyW;          // w - dark energy equation of state
    double darkMatterRatio;      // Ratio of dark matter to total matter
    double initialEnergyDensity; // Total initial energy density
}; 