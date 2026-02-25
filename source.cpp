
#include<cmath>
#include "source.h"
#include <ctime>
#include <chrono>

std::string source::get_name()
{
  return type;
}

double source::get_activity()
{
  return initial_activity * std::exp(-2 * half_life / std::log(2));
}