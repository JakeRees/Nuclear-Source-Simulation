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

    bool is_valid_date(int year, int month, int day) 
    {
      std::tm date = {};
      date.tm_year = year - 1900;
      date.tm_mon = month - 1;
      date.tm_mday = day;

      std::tm original = date;
      mktime(&date);

      // If mktime changed any values, the date was invalid
      return date.tm_mday == original.tm_mday &&
            date.tm_mon == original.tm_mon &&
            date.tm_year == original.tm_year;
    }
};

class Source
{
private:
  std::string type = {"None"};
  double initial_activity = {100.0};
  Date aquired = {Date(1900, 1, 1)};
  int id = {0};
  static std::set<int> used_ids;
  double half_life = {86400.0};
  std::string decay_type = {"gamma"};

public:
  Source() = default ;

  Source(std::string source_type, double activity, Date initial_acquired,
        double half_life, int source_id, std::string decay_type)
  {
    set_type(source_type);
    set_initial_activity(activity);
    set_aquiry_date(initial_acquired);
    set_half_life(half_life);
    set_id(source_id);
    set_decay_type(decay_type);
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
  Date get_aquiry_date();
  double get_initial_activity();
  int get_id();
  double get_half_life();
  long long get_age(int year, int month, int day);
  long long get_age();
  std::string get_decay_type();

  void set_type(std::string new_type);
  void set_aquiry_date(Date = Date(1900, 1, 1));
  void set_initial_activity(double new_activity);
  void set_id(int new_id);
  void set_half_life(double new_half_life);
  void set_decay_type(std::string new_type);

};

#endif