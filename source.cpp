#include<iostream>
#include<cmath>
#include "Source.h"
#include <ctime>
#include <cmath>
#include <set>

// This set is shared across all source objects
std::set<int> Source::used_ids;

int64_t days_from_epoch(int year, unsigned month, unsigned day)
{
  // Returns the time between in days between a given date and 01/03/1970

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

long long Source::get_age(int year, int month, int day)
{
  // Returns the difference in seconds between source aquiry date and given date
  int64_t days1 = days_from_epoch(aquired.year, aquired.month, aquired.day);
  int64_t days2 = days_from_epoch(year, month, day);

  return (days2 - days1) * 86400LL; // seconds
}

std::string Source::get_type()
{
  return type;
}

double Source::get_activity()
{
  // Calculates the source activity at the current date
  time_t now = time(0);
  tm* local_time = localtime(&now);

  int year = 1900 + local_time->tm_year;
  int month = 1 + local_time->tm_mon;
  int day = local_time->tm_mday;
  
  return initial_activity * pow(2.0f, -get_age(year, month, day)/half_life);
}

double Source::get_activity(int year, int month, int day)
{
  // Calculates the source activity at a given date
  if ((year < aquired.year) ||  (month < aquired.month) || (day < aquired.day)) return 0.0;
  return initial_activity * pow(2.0f, -get_age(year, month, day)/half_life);
}

double Source::get_initial_activity()
{
  return initial_activity;
}

int Source::get_id()
{
  return id;
}

double Source::get_half_life()
{
  return half_life;
}

void Source::set_type(std::string new_type)
{
  type = new_type;
}

void Source::set_initial_activity(double new_activity)
{
  if (new_activity < 0)
  {
    std::cout << "\033[1;31mError: Activity must be positive\033[0m\n" << std::endl;
    return;
  }

  initial_activity = new_activity;
}

void Source::set_id(int new_id) {
    if (used_ids.count(new_id)) {
        std::cerr << "\033[1;31mError: ID " << new_id 
                  << " is already in use\033[0m\n" << std::endl;
        
    } else {
        used_ids.insert(new_id);
        id = new_id;
    }
}

void Source::set_half_life(double new_half_life)
{
  if (new_half_life < 0)
  {
    std::cout << "\033[1;31mError: Half life must be positive\033[0m\n" << std::endl;
    return;
  }

  half_life = new_half_life;
}