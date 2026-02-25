#include<iostream>
#include<iomanip>
#include <ctime>
#include <chrono>
#include "source.h"

int main()
{
  
  // Instantiate material (later using config file) here
  source target_source = source("NA-22", 2354, Date(1954, 4, 14));

  std::cout << "Source name: " << target_source.get_name();

  // Run simulation here
}