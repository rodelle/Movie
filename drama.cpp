#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap
#include <istream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "drama.h"

Drama::Drama(const std::string& title, const std::string& director, int year)
  : Movie(title, director, year)
{
  assert(year >= kMinYear); 
  assert(year <= kMaxYear);

  Movie::validate_input();
}

Drama::Drama(std::istream& input)
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

  Movie::validate_input();
}

std::ostream& operator<<(std::ostream& out, const Drama& movie)
{
  out << std::left 
    << std::setw(Drama::kTitleDisplayWidth) << movie.title_
    << std::setw(Drama::kDirectorDisplayWidth) << movie.director_
    << std::setw(Drama::kYearDisplayWidth) << movie.year_;

 return out;
}

Drama::Drama(const Drama& other)
{
  director_ = other.director_;
  title_ = other.title_;
  year_ = other.year_;
}

Drama::~Drama()
{

}

Drama& Drama::operator=(Drama other)
{
  std::swap(director_, other.director_);
  std::swap(title_, other.title_);
  std::swap(year_, other.year_);
  return *this;
}

// Prints the table headers to view the movie data in a table format
void Drama::PrintTableHeader()
{
  std::cout << std::left 
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR" 
    << std::setw(kYearDisplayWidth) << "YEAR"; 
}

// Sorted by director then title 
bool Drama::operator<(const Movie& other) const
{
  int compare = 0;
  const Drama& o = static_cast<const Drama&>(other);

  compare = director_.compare(o.director_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  compare = title_.compare(o.title_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  return false; // equal to each other
}

bool Drama::operator>(const Movie& other) const
{
  return !((*this < other) || (*this == other)); 
}

bool Drama::operator==(const Movie& other) const
{
  const Drama& o = static_cast<const Drama&>(other);
  return (year_ == o.year_) 
    && (director_.compare(o.director_) == 0)
    && (title_.compare(o.title_) == 0);
}

bool Drama::operator!=(const Movie& other) const
{
  return !(*this == other);
}