#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include <ctime>
#include "Source.h"

class Detector
{
private:
  std::string type = {"None"};
  bool is_on = {false};
  Date turned_on = {Date(0, 1, 1)};
  int total_counts = {0};
  double efficiency = {1};

public:
  Detector() = default;

  Detector(std::string detector_type, double detector_efficiency)
  {
    set_type(detector_type);
    set_efficiency(detector_efficiency);
  }

  ~Detector(){}
  std::string get_type();
  int get_counts();
  double get_efficiency();

  void set_type(std::string detector_type);
  void set_efficiency(double new_efficiency);
  void reset_counts();
  void flip_status();

  int measure(Source source, double time);
};

#endif