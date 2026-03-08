#include<iostream>
#include<cmath>
#include "detector.h"

std::string detector::get_name()
{
  return name;
}

void detector::flip_status()
{
  on = !on;
}