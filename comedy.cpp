#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap
#include <istream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "comedy.h"

Comedy::Comedy(const std::string& title, const std::string& director, int year)
  : Movie(title, director, year)
{
  assert(year >= kMinYear); 
  assert(year <= kMaxYear);

  validate_input();
}

Comedy::Comedy(std::istream& input)
  :Movie("", "", kMinYear)
{
  std::string title, director, year;

  std::getline(input, title, ',');
  std::getline(input, director, ',');
  std::getline(input, year);

  boost::algorithm::trim(title);
  boost::algorithm::trim(director);
  boost::algorithm::trim(year);

  if(!input.fail()) {
    title_ = title;
    director_ = director;
    year_ = boost::lexical_cast<int>(year.c_str());
  }

  validate_input();
}

std::ostream& operator<<(std::ostream& out, const Comedy& movie)
{
  out << std::left 
    << std::setw(Comedy::kTitleDisplayWidth) << movie.title_
    << std::setw(Comedy::kDirectorDisplayWidth) << movie.director_
    << std::setw(Comedy::kYearDisplayWidth) << movie.year_;

 return out;
}

Comedy::Comedy(const Comedy& other)
{
  director_ = other.director_;
  title_ = other.title_;
  year_ = other.year_;
}

Comedy::~Comedy()
{

}

Comedy& Comedy::operator=(Comedy other)
{
  std::swap(director_, other.director_);
  std::swap(title_, other.title_);
  std::swap(year_, other.year_);
  return *this;
}

// Prints the table headers to view the movie data in a table format
void Comedy::PrintTableHeader()
{
  std::cout << std::left 
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR" 
    << std::setw(kYearDisplayWidth) << "YEAR"; 
}

// Sorted by title then date 
bool Comedy::operator<(const Movie& other) const
{
  int compare = 0;
  const Comedy& o = static_cast<const Comedy&>(other);

  compare = title_.compare(o.title_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  compare = year_ - o.year_;
  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  return false; // equal to each other
}

bool Comedy::operator>(const Movie& other) const
{
  return !((*this < other) || (*this == other)); 
}

bool Comedy::operator==(const Movie& other) const
{
  const Comedy& o = static_cast<const Comedy&>(other);
  return (year_ == o.year_) 
    && (director_.compare(o.director_) == 0)
    && (title_.compare(o.title_) == 0);
}

bool Comedy::operator!=(const Movie& other) const
{
  return !(*this == other);
}
