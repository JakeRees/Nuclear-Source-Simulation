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
  std::string type = {"None"};
  bool on = {false};
  Date turned_on = {Date(0, 1, 1)};

public:
  detector() = default ;

  detector(std::string detector_type) :
    type{detector_type}
    {}

  ~detector(){std::cout << "\nDestroying " << type << " object" << std::endl;}
  std::string get_name();

};

#endif