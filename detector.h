#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include "Source.h"

struct Efficiency {
    double gamma;
    double beta;
    double alpha;
    Efficiency(double g, double b, double a) : 
      gamma(g), beta(b), alpha(a) 
      {}

    double get(const std::string& type) const {
        if (type == "gamma") return gamma;
        if (type == "beta")  return beta;
        if (type == "alpha") return alpha;
        
        std::cout << "\033[1;31mError: Unknown emitter type: " << type 
                  << "\033[0m" << std::endl;
        return 0.0;
    }
};

class Detector
{
private:
  std::string type = {"None"};
  bool is_on = {false};
  int total_counts = {0};
  Efficiency efficiency = {Efficiency(1, 1, 1)};

public:
  Detector() = default;

  Detector(std::string detector_type, double gamma_eff,
           double beta_eff, double alpha_eff)
  {
    set_type(detector_type);
    set_efficiency(gamma_eff, beta_eff, alpha_eff);
  }

  ~Detector(){}
  
  std::string get_type();
  int get_counts();
  double get_efficiency(std::string type);

  void set_type(std::string detector_type);
  void set_efficiency(double gamma_eff = 1, double beta_eff = 1, double alpha_eff = 1);
  void reset_counts();
  void flip_status();

  int measure(Source source, double time = 1);
};

#endif