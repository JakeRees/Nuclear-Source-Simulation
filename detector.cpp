#include<iostream>
#include<cmath>
#include "Detector.h"

std::string Detector::get_type()
{
  return type;
}

void Detector::flip_status()
{
  on = !on;
}
