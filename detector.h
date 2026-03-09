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
  int total_counts;

public:
  Detector() = default ;

  Detector(std::string detector_type) :
    type{detector_type}
    {}

  ~Detector(){}
  std::string get_type();
  void flip_status();
  int measure(Source source, double time);


};

#endif