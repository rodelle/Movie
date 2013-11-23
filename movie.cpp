#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap
#include <istream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "movie.h"
 
const int Movie::kTitleDisplayWidth = 20;
const int Movie::kDirectorDisplayWidth = 15;
const int Movie::kYearDisplayWidth = 4;

const int Movie::kMinYear = 1800;
const int Movie::kMaxYear = 2100;

Movie::Movie(const std::string& title, const std::string& director, int year)
  : title_(title), director_(director), year_(year)
{
  assert(year >= kMinYear); 
  assert(year <= kMaxYear);

  validate_input();
}

Movie::Movie(std::istream& input)
  :title_(""), director_(""), year_(kMinYear)
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

void Movie::validate_input()
{
  if(year_ < kMinYear)
    year_ = kMinYear;
  if(year_ > kMaxYear)
    year_ = kMaxYear;
}

std::ostream& operator<<(std::ostream& out, const Movie& movie)
{
  out << std::left 
    << std::setw(Movie::kTitleDisplayWidth) << movie.title_
    << std::setw(Movie::kDirectorDisplayWidth) << movie.director_
    << std::setw(Movie::kYearDisplayWidth) << movie.year_;

 return out;
}

Movie::Movie(const Movie& other)
{
  director_ = other.director_;
  title_ = other.title_;
  year_ = other.year_;
}

Movie::~Movie()
{

}

Movie& Movie::operator=(Movie other)
{
  std::swap(director_, other.director_);
  std::swap(title_, other.title_);
  std::swap(year_, other.year_);
  return *this;
}

// Prints the table headers to view the movie data in a table format
void Movie::PrintTableHeader()
{
  std::cout << std::left 
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR" 
    << std::setw(kYearDisplayWidth) << "YEAR"; 
}

// Sorted by title then director
bool Movie::operator<(const Movie& other) const
{
  int compare = 0;
  compare = title_.compare(other.title_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;
  
  compare = director_.compare(other.director_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  return false; // equal to each other
}

bool Movie::operator>(const Movie& other) const
{
  return !(*this < other); 
}

bool Movie::operator==(const Movie& other) const
{
  return (director_.compare(other.director_) == 0)
      && (title_.compare(other.title_) == 0);
}

bool Movie::operator!=(const Movie& other) const
{
  return !(*this == other);
}
