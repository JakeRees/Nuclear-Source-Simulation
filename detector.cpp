#include<iostream>
#include<cmath>
#include <random>
#include <algorithm>
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
  
  // Determine mean expected counts - accounting for detector efficiency
  double expected_counts = source.get_activity() * time ;
  expected_counts *= efficiency.get(source.get_decay_type());
  // Using a poisson distribution to more accurately simulate real physics
  static std::random_device random_seed;
  static std::mt19937 gen(random_seed());
  std::poisson_distribution<int> poisson(expected_counts);
  int count = poisson(gen);
  total_counts += count;

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

double Detector::get_efficiency(std::string type)
{
  std::transform(type.begin(), type.end(), type.begin(), ::tolower);
  
  if (type == "beta")
  {
    return efficiency.beta;
  }
  else if (type == "alpha")
  {
    return efficiency.alpha;
  }

  // Default to gamma efficiency
  return efficiency.gamma;
}

void Detector::set_type(std::string name)
{
  type = name;
}

void Detector::set_efficiency(double gamma_eff, double beta_eff, double alpha_eff)
{

  for (double eff : {gamma_eff, beta_eff, alpha_eff})
  {
    if (eff < 0 || eff > 1)
    {
      std::cout << "\033[1;31mError: Efficiency must be a positive decimal "
                << "between 0 an 1\033[0m" << std::endl;
      return;
    }
  }

  efficiency.gamma = gamma_eff;
  efficiency.beta  = beta_eff;
  efficiency.alpha = alpha_eff;
}
