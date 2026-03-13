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

struct Simulation 
{
  string detector;
  int time;

  Simulation(string detector, double time)
  {
    this->detector = detector;
    this->time = time;
  }
};

void read_config(string file_name, vector<Source>& sources, vector<Detector>& detectors)
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
      string decay_type;

      // Ensures data is of expected type (double, int, string)
      if (converter >> id >> activity >> half_life >> date_string >> decay_type)
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

        sources.emplace_back(name, activity, Date(year, month, day),
                             half_life, id, decay_type);
      }
      else
      {
          bad_lines.push_back(line_number);
      }
    }
    else if (identifier == "DETECTOR")
    {

      double gamma_eff, beta_eff, alpha_eff;

      if (converter >> gamma_eff >> beta_eff >> alpha_eff)
      {
        string name;
        std::getline(converter, name);

        // Remove leading whitespace
      name.erase(0, name.find_first_not_of(" "));
      detectors.emplace_back(name, gamma_eff, beta_eff, alpha_eff);
      }
      else
      {
        bad_lines.push_back(line_number);
      }
    }
  }

  if (!bad_lines.empty())
  {
    cout << "\033[1;33mWarning: Couldn't read data from following lines: ";
    for (std::size_t i = 0; i < bad_lines.size(); i++)
    {
      cout << bad_lines[i] << ", ";
    }

    cout << "these lines have been skipped\033[0m\n";
  }
}

int main()
{

  vector<Source> sources; 
  vector<Detector> detectors;

  read_config("config.txt", sources, detectors);
  
  int count = 0;
  int simulation_time = 1;

  for(Detector& detector : detectors) 
    detector.flip_status();

  // For each source print out the source info and measure with each detector
  for(Source& source : sources)
  {
    cout << source.get_type() << " (Id: " << source.get_id() << "): " 
         << "\nSource Age: " << source.get_age() / 86400.0 / 365.0 << " years"
         << "\nHalf Life: " << source.get_half_life() / 86400.0 / 365.0 << " years"
         << "\nInitial Activity: " << source.get_initial_activity()
         << "\nCurrent Activity: " << source.get_activity()
         << "\nDecay Type: " << source.get_decay_type();

    cout << "\nCounts detected by: ";
    for(Detector& detector : detectors)
    {
      count = detector.measure(source, simulation_time);
      cout << detector.get_type() << ": " << count << ", ";
    }

    cout << "\n\n";
  }

  for(Detector& detector : detectors)
  {
    std::cout << "Detector name: " << detector.get_type()
              << " | Efficiency: Gamma: " << detector.get_efficiency("gamma") * 100 
              << "%, Beta: " << detector.get_efficiency("beta") * 100
              << "%, Alpha: " << detector.get_efficiency("alpha") * 100 << "%\n";

    std::cout << "A total of " << detector.get_counts() << " counts where detected by"
              << " this detector over a total of " << simulation_time << " seconds"
              << " (From every source)\n\n\n";

    // Reset detector after simulation has been complete
    detector.reset_counts();
  }
}