#include<iostream>
#include<cmath>
#include <random>
#include "Detector.h"

std::string Detector::get_type()
{
  return type;
}

void Detector::flip_status()
{
  is_on = !is_on;
}

int Detector::measure(Source source, double time) {
  // Gives an estimate for the counts produced over a given time interval.
  if (!is_on) {
    std::cout << "\n\033[1;33mWarning: Detector is off\033[0m" << std::endl;
    return 0;
  }  
  
  double expected_counts = source.get_activity() * time;
  // Using a poisson distribution to more accurately simulate real physics
  static std::random_device random_seed;
  static std::mt19937 gen(random_seed());
  std::poisson_distribution<int> poisson(expected_counts);
  int count = poisson(gen);

  return count;
}
