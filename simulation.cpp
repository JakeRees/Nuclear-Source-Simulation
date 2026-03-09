#include<iostream>
#include<iomanip>
#include <ctime>
#include <chrono>
#include "Source.h"
#include "detector.h"

int main()
{

  // Instantiate material (later using config file) here
  Source target_source = Source("NA-22", 14234544, Date(2025, 4, 14), 31536000*10, 1);
  Source target_source_two = Source("NA-22", 14234544, Date(2025, 4, 14), 31536000*10, 2);
  Detector current_detector = Detector("Scintillator");

  std::cout << "Source name: " << target_source.get_type();
  std::cout << "\nDetector name: " << current_detector.get_type();

  std::cout << "Detected Counts: " << current_detector.measure(target_source, 1);
  current_detector.flip_status();
  std::cout << "Detected Counts: " <<  current_detector.measure(target_source, 1);

  //std::time_t t = std::time(nullptr);
  //std::tm* now = std::localtime(&t);
  //std::cout << "\nSource age: " << target_source.get_age(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
  //std::cout << "\nSource activity: " << target_source.get_activity();

  // Run simulation here
}