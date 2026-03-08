#include<iostream>
#include<cmath>
#include "source.h"
#include <ctime>

int64_t days_from_epoch(int year, unsigned month, unsigned day)
{
  // returns the time between in days between a given date and 01/03/1970

  // Treat January and February as months of the previous year
  if (month <= 2) {
      year -= 1;
      month += 12;
  }

  // Gregorian calender repeats every 400 years
  int era = year / 400;

  // Calculates year within block, day within year, and day within block
  int year_of_era = year - era * 400;
  int day_of_year = (153 * (month - 3) + 2) / 5 + day - 1;
  int days_of_era = year_of_era * 365 + year_of_era / 4 - year_of_era / 100
                    + day_of_year;

  // Convert to days (146097 days in each block, 719468 days between 0-1970)
  return era * 146097 + days_of_era - 719468;
}

long long source::get_age(int year, int month, int day)
{
  // Returns the difference in seconds between source aquiry date and given date
  int64_t days1 = days_from_epoch(aquired.year, aquired.month, aquired.day);
  int64_t days2 = days_from_epoch(year, month, day);

  return (days2 - days1) * 86400LL; // seconds
}

std::string source::get_name()
{
  return name;
}

double source::get_activity()
{
  return initial_activity * std::exp(-2 * half_life / std::log(2));
}

double source::get_initial_activity()
{
  return initial_activity;
}

int source::get_id()
{
  return id;
}

double source::get_half_life()
{
  return half_life;
}

void source::set_name(std::string new_name)
{
  name = new_name;
}

void source::set_initial_activity(double new_activity)
{
  initial_activity = new_activity;
}

void source::set_id(int new_id)
{
  id = new_id;
}

void source::set_half_life(double new_half_life)
{
  half_life = new_half_life;
}