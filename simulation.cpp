#include<iostream>
#include<iomanip>
#include <ctime>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>
#include "Source.h"
#include "Detector.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;

void read_config(string file_name, vector<Source>& sources, Detector& detector)
{
  /* Open a file and read the coloumns*/
  std::ifstream file(file_name);
  vector<int> bad_lines;

  if (!file) 
  {
    // Throw error and exit application if file is unable to be opened
    std::cerr << "\033[1;31mFailed to open file: " << file_name << "\033[0m\n";
    abort();
  }

  int line_number = 0;
  string line;
  string identifier;

  while (std::getline(file, line))
  {
    line_number += 1;
    std::istringstream converter(line);

    if (converter >> identifier && identifier == "SOURCE")
    {

      double activity;
      double half_life;
      int id;
      string name;
      string date_string;

      // Ensures data is of expected type (double, int, string)
      if (converter >> id >> activity >> half_life >> date_string)
      {
        std::istringstream iss(date_string);
        std::string part;
        
        int year, month, day;

        std::getline(iss, part, '-');
        year = std::stoi(part);

        std::getline(iss, part, '-');
        month = std::stoi(part);

        std::getline(iss, part, '-');
        day = std::stoi(part);

        std::getline(converter, name);

        // Remove leading whitespace
        name.erase(0, name.find_first_not_of(" "));

        sources.emplace_back(name, activity, Date(year, month, day), half_life, id);
      }
      else
      {
          bad_lines.push_back(line_number);
      }
    }
    else if (identifier == "DETECTOR")
    {

      string name;
      std::getline(converter, name);

      // Remove leading whitespace
      name.erase(0, name.find_first_not_of(" "));
      detector = Detector(name);

    }

  }
}

int main()
{

  // Instantiate material (later using config file) here
  //Source target_source = Source("NA-22", 1000, Date(2025, 4, 14), 31536000, 1);
  //Source target_source_two = Source("CO-50", 500, Date(2022, 1, 3), 2354345, 1);
  vector<Source> sources; 
  Detector detector;

  read_config("config.txt", sources, detector);
  int source_count = sources.size();

  for (int i = 0; i < source_count; i++)
  {
    cout << sources[i].get_id() << std::endl;
  }

  //std::cout << "Source name: " << target_source.get_type();
  //std::cout << "\nDetector name: " << current_detector.get_type();

  //std::cout << "Detected Counts: " << current_detector.measure(target_source, 1);
  //current_detector.flip_status();
  //std::cout << "Detected Counts: " <<  current_detector.measure(target_source, 1);

  //std::time_t t = std::time(nullptr);
  //std::tm* now = std::localtime(&t);
  //std::cout << "\nSource age: " << target_source.get_age(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
  //std::cout << "\nSource activity: " << target_source.get_activity();

  // Run simulation here
}