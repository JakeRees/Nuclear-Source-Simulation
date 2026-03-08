#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include <ctime>
#include "source.h"

class detector
{
private:
  std::string name = {"None"};
  bool on = {false};
  Date turned_on = {Date(0, 1, 1)};

public:
  detector() = default ;

  detector(std::string detector_type) :
    name{detector_type}
    {}

  ~detector(){std::cout << "\nDestroying " << name << " object" << std::endl;}
  std::string get_name();
  void flip_status();


};

#endif