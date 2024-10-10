// EnergyDistribution.hh
#ifndef ENERGYDISTRIBUTION_HH
#define ENERGYDISTRIBUTION_HH

#include <vector>
#include <random>

class EnergyDistribution {
public:
    EnergyDistribution();
    ~EnergyDistribution();
    double Generate();

private:
    std::vector<double> energy_ranges;
    std::vector<double> probabilities;
    std::discrete_distribution<> dist;
    std::mt19937 generator;
};

#endif

