#include<iostream>
#include<cmath>
#include "source.h"
#include <ctime>

long long days_from_epoch(int y, int m, int d)
{
  // Returns the number of days distance from the year 1970
  y -= m <= 2;
  int64_t era = (y >= 0 ? y : y - 399) / 400;
  int year = static_cast<unsigned>(y - era * 400);
  int day_in_year = (153 * (m + (m > 2 ? -3 : 9)) + 2)/5 + d - 1;
  int day = year * 365 + year/4 - year/100 + day_in_year;
  return era * 146097 + day - 719468;
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
  return type;
}

double source::get_activity()
{
  return initial_activity * std::exp(-2 * half_life / std::log(2));
}