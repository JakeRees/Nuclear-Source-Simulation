/*
                              Jake Rees, 11307374
                           University of Manchester

This program reads, uses source and detector objects generated with information
given in a config file to run a basic nuclear decay detection simulation.
*/

#include<iostream>
#include<iomanip>
#include <ctime>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>
#include <optional>
#include "Source.h"
#include "Detector.h"
using std::cout;
using std::cin;
using std::string;
using std::vector;

void read_config(string file_name, vector<Source>& sources, std::optional<Detector>& detector)
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
      if (!detector.has_value())
      {
        string name;
        std::getline(converter, name);

        // Remove leading whitespace
        name.erase(0, name.find_first_not_of(" "));
        detector = Detector(name);
      }
      else
      {
        cout << "\033[1;33mWarning: Attempted to create multiple detector objects\033[0m";
      }
    }
  }
}

int main()
{

  vector<Source> sources; 
  std::optional<Detector> detector = std::nullopt;

  read_config("config.txt", sources, detector);
  int source_count = sources.size();
  
  int count = 0;
  int long_count = 0;
  int simulation_time = 1;
  int long_simulation_time = 86400;
  (*detector).flip_status();

  for (int i = 0; i < source_count; i++)
  {
    cout << sources[i].get_type() << " (Id: " << sources[i].get_id() << "): " 
        << "\nSource Age: " << sources[i].get_age() / 86400.0 / 365.0 << " years"
        << "\nHalf Life: " << sources[i].get_half_life() / 86400.0 / 365.0 << " years"
        << "\nInitial Activity: " << sources[i].get_initial_activity()
        << "\nCurrent Activity: " << sources[i].get_activity() << "\n\n";

        count += (*detector).measure(sources[i], simulation_time);
        long_count += (*detector).measure(sources[i], long_simulation_time);
  }

  std::cout << "Detector name: " << (*detector).get_type() << "\n\n";

  std::cout << "A total of " << count << " counts where detected by this detector"
            << " over a total of " << simulation_time << " seconds\n\n";

  std::cout << "A total of " << long_count << " counts where detected by this detector"
            << " over a total of " << long_simulation_time << " seconds\n";
}