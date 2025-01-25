# Cosmic Architect

A C++ simulation of universe evolution based on fundamental cosmological parameters.

## Overview

Cosmic Architect simulates different possible universes and calculates their evolution through major milestones, from the Big Bang to their ultimate fate, based on fundamental physical parameters.

## Codebase Structure

### 1. Core Classes

#### UniverseParameters
Holds fundamental parameters of a universe:
- Matter density (Ω_m)
- Dark energy density (Ω_Λ)
- Hubble constant (H₀)
- Matter/antimatter ratio
- Dark energy equation of state (w)
- Dark matter ratio
- Initial energy density

### 2. Milestone System

#### Base Milestone Class
- Abstract base class for all cosmic events
- Each milestone calculates its timestamp in Gyr (billion years)
- Provides JSON serialization

#### Key Milestone Types
- **BigBang**: t = 0
- **Inflation**: Very early universe (~10⁻⁴⁹ Gyr)
- **ParticleEra**: Formation of fundamental particles
- **NucleosynthesisBBN**: Formation of light elements
- **Recombination**: Atoms form, universe becomes transparent
- **DarkAges**: Period before first stars
- **FirstStars**: Initial star formation
- **GalaxyFormation**: Galaxy assembly
- **AcceleratedExpansion**: Dark energy dominance

#### Universe Endings
- **BigRip**: Universe tears apart (w < -1)
- **BigCrunch**: Universe recollapses (Ω > 1)
- **HeatDeath**: Eternal expansion

### 3. Testing

The testing framework includes various universe scenarios:
1. Baryon-Only Universe
2. Matter-Dominated Universe
3. Phantom Energy Universe
4. Radiation-Baryon Universe
5. Baryon-Poor Universe

Each scenario tests milestone timings and universe fate.

### 4. Key Physics

Universe fate is determined by:
- Total density (Ω_total)
- Dark energy equation of state (w)
- Matter/dark matter ratio
- Initial energy conditions

### 5. Usage Example

```cpp
// Create universe with parameters
SimulatedUniverse universe(
    matterDensity,
    darkEnergyDensity,
    hubbleConstant,
    matterAntimatterRatio
);

// Generate timeline of events
auto timeline = universe.generateTimeline();

// Export to JSON
timeline->saveToFile("universe_timeline.json");
```

## Building

```bash
# Create build directory
mkdir -p backend/build
cd backend/build

# Configure and build
cmake ..
make

# Run tests
./tests/milestone_tests
```

## Dependencies
- C++17 or later
- CMake 3.10 or later
- Google Test (for testing) 