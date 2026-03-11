#ifndef SOURCE_H
#define SOURCE_H

#include<iostream>
#include<string>
#include<cmath>
#include <ctime>
#include <set>

struct Date {
    int year;
    int month;
    int day;

    Date(int y, int m, int d) : 
      year(y), month(m), day(d) 
      {}
};

class Source
{
private:
  std::string type = {"None"};
  double initial_activity = {0.0};
  Date aquired = Date(1900, 0, 1);
  int id = {0};
  static std::set<int> used_ids;
  double half_life = {1.0};

public:
  Source() = default ;

  Source(std::string source_type, double activity, Date initial_acquired,
        double half_life, int source_id)
  {
    set_type(source_type);
    set_initial_activity(activity);
    aquired = initial_acquired;
    set_half_life(half_life);
    set_id(source_id);
  }

  ~Source() 
  {
    if (used_ids.count(id)) {
      used_ids.erase(id);
    }
  }

  std::string get_type();
  double get_activity();
  double get_activity(int year, int month, int day);
  double get_initial_activity();
  int get_id();
  double get_half_life();
  long long get_age(int year, int month, int day);
  long long get_age();

  void set_type(std::string new_type);
  void set_initial_activity(double new_activity);
  void set_id(int new_id);
  void set_half_life(double new_half_life);

};

#endif