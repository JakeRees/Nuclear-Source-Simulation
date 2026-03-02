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


  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);
  std::cout << "\nSource age: " << target_source.get_age(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);

  // Run simulation here
}