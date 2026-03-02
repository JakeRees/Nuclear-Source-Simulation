#ifndef SOURCE_H
#define SOURCE_H

#include<iostream>
#include<string>
#include<cmath>
#include <ctime>

struct Date {
    int year;
    int month;
    int day;

    Date(int y, int m, int d) : 
      year(y), month(m), day(d) 
      {}
};

class source
{
private:
  std::string type {"None"};
  double initial_activity = {0.0};
  Date aquired = Date(1900, 0, 1);
  int id = {0};
  double half_life = {1.0};

public:
  source() = default ;

  source(std::string particle_type, double activity, Date initial_aquired) :
    type{particle_type}, initial_activity{activity}, aquired{initial_aquired}
    {}

  ~source(){std::cout << "\nDestroying " << type << " object" << std::endl;}
  std::string get_name();
  double get_activity();
  long long get_age(int year, int month, int day);

};

#endif