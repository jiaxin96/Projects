#include "Date.hpp"
#include <set>
#include <sstream>
#include <string>
using namespace std;
Date::Date() : m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0) {}
Date::Date(int y, int mon, int d, int h, int min) : m_year(y), m_month(mon), m_day(d), m_hour(h), m_minute(min) {}

Date::Date(string date) { *this = Date::stringToDate(date); }

int Date::getYear(void) const { return m_year; }
void Date::setYear(int year) { m_year = year; }

int Date::getMonth(void) const { return m_month; }
void Date::setMonth(int month) { m_month = month; }
int Date::getDay(void) const { return m_day; }
void Date::setDay(int day) { m_day = day; }

int Date::getHour(void) const { return m_hour; }
void Date::setHour(int hour) { m_hour = hour; }

int Date::getMinute(void) const { return m_minute; }
void Date::setMinute(int minute) { m_minute = minute; }

bool Date::isValid(Date date) {
  if (date.m_year > 9999 || date.m_year < 1000 || date.m_month > 12 || date.m_month < 1
    || date.m_day > 31 || date.m_day < 1 || date.m_hour > 23 || date.m_hour < 0 ||
    date.m_minute < 0 || date.m_minute > 59) return false;

    if (date.m_year % 400 == 0 || (date.m_year % 4 == 0 && date.m_year % 100 != 0)) {
      switch (date.m_month) {
        case 2:
          if (date.m_day > 29) return false;
          break;
        case 4:
        case 6:
        case 9:
        case 11:
          if (date.m_day > 30) return false;
      }
    } else {
            switch (date.m_month) {
        case 2:
          if (date.m_day > 28) return false;
          break;
        case 4:
        case 6:
        case 9:
        case 11:
          if (date.m_day > 30) return false;
      }
    }
  return true;
}
bool stringIsInt(string str) {
  int l = str.length();
  for (int i = 0; i < l; ++i) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

Date Date::stringToDate(std::string dateString) {
  if (dateString.length() != 16) {
    return Date(0, 0, 0, 0, 0);
  }
  string year = dateString.substr(0, 4);
  if (!stringIsInt(year)) {
    return Date(0, 0, 0, 0, 0);
  }
  if (dateString[4] != '-') {
    return Date(0, 0, 0, 0, 0);
  }

  string month = dateString.substr(5, 2);
  if (!stringIsInt(month)) {
    return Date(0, 0, 0, 0, 0);
  }
  if (dateString[7] != '-') {
    return Date(0, 0, 0, 0, 0);
  }

  string day = dateString.substr(8, 2);
  if (!stringIsInt(day)) {
    return Date(0, 0, 0, 0, 0);
  }
  if (dateString[10] != '/') {
    return Date(0, 0, 0, 0, 0);
  }

  string hour = dateString.substr(11, 2);
  if (!stringIsInt(hour)) {
    return Date(0, 0, 0, 0, 0);
  }
  if (dateString[13] != ':') {
    return Date(0, 0, 0, 0, 0);
  }
  string minute = dateString.substr(14, 2);
  if (!stringIsInt(minute)) {
    return Date(0, 0, 0, 0, 0);
  }

  Date temp = Date(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str()),
                   atoi(hour.c_str()), atoi(minute.c_str()));
  return temp;
}
std::string int2string(int num) {
  std::stringstream ss;
  std::string str;
  ss << num;
  ss >> str;
  if (num > 9)
    return str;
  return ('0' + str);
}
std::string Date::dateToString(Date date) {
  if (!Date::isValid(date)) {
    return "0000-00-00/00:00";
  }
  string dateStr = int2string(date.m_year) + '-' + int2string(date.m_month) +
                   '-' + int2string(date.m_day) + '/' +
                   int2string(date.m_hour) + ':' + int2string(date.m_minute);
  return dateStr;
}
Date &Date::operator=(const Date &date) {
  m_year = date.m_year;
  m_month = date.m_month;
  m_day = date.m_day;
  m_hour = date.m_hour;
  m_minute = date.m_minute;
  return *this;
}
bool Date::operator==(const Date &date) const {
  if (m_year == date.m_year && m_month == date.m_month && m_day == date.m_day &&
      m_hour == date.m_hour && m_minute == date.m_minute)
    return true;
  return false;
}
bool Date::operator<(const Date &date) const {
  if (m_year < date.m_year) {
    return true;
  } else if (m_year > date.m_year) {
    return false;
  } else {
    if (m_month < date.m_month) {
      return true;
    } else if (m_month > date.m_month) {
      return false;
    } else {
      if (m_day < date.m_day) {
        return true;
      } else if (m_day > date.m_day) {
        return false;
      } else {
        if (m_hour < date.m_hour) {
          return true;
        } else if (m_hour > date.m_hour) {
          return false;
        } else {
          if (m_minute < date.m_minute) {
            return true;
          } else if (m_minute > date.m_minute) {
            return false;
          } else {
            return false;
          }
        }
      }
    }
  }
}


bool Date::operator>(const Date &date) const {
  return (!(*this < date) && !(*this == date));
}
bool Date::operator>=(const Date &date) const {
  return ((*this == date) || (*this > date));
}
bool Date::operator<=(const Date &date) const {
  return ((*this == date) || (*this < date));
}