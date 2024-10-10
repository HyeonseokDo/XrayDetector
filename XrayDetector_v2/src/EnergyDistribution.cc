// EnergyDistribution.cc
#include "EnergyDistribution.hh"

EnergyDistribution::EnergyDistribution()
    : generator(std::random_device()()),
      energy_ranges({0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140}),
      probabilities({0.02, 0.27, 0.96, 2.34, 3.68, 5.04, 5.87, 6.52, 6.66, 6.74, 6.61, 6.34, 5.94, 5.65, 5.46, 4.96, 4.53, 4.21, 3.82, 3.17, 2.9, 2.55, 1.99, 1.62, 1.14, 0.71, 0.29, 0.01}),
	  dist(probabilities.begin(), probabilities.end())
{}

EnergyDistribution::~EnergyDistribution() {}

double EnergyDistribution::Generate()
{
    int index = dist(generator);
    double lower_bound = energy_ranges[index];
    double upper_bound = energy_ranges[index + 1];
    std::uniform_real_distribution<> uniform_dist(lower_bound, upper_bound);
    return uniform_dist(generator);
}

