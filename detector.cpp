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
  
  double expected_counts = source.get_activity() * time * efficiency;
  // Using a poisson distribution to more accurately simulate real physics
  static std::random_device random_seed;
  static std::mt19937 gen(random_seed());
  std::poisson_distribution<int> poisson(expected_counts);
  int count = poisson(gen);

  return count;
}

void Detector::reset_counts()
{
  total_counts = 0;
}

int Detector::get_counts()
{
  return total_counts;
}

double Detector::get_efficiency()
{
  return efficiency;
}

void Detector::set_type(std::string name)
{
  type = name;
}

void Detector::set_efficiency(double new_efficiency)
{
  if (new_efficiency < 0 || new_efficiency > 1)
  {
    std::cout << "\033[1;31mError: Efficiency must be a positive decimal "
              << "between 0 an 1\033[0m" 
              << std::endl;
    return;
  }

  efficiency = new_efficiency;
}
