#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap
#include <istream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "comedy.h"

Comedy::Comedy(
  const std::string& title,
  const std::string& director,
  const std::string& data)
{
  Movie::Init(title, director, data);
}

Comedy::Comedy(std::istream& input)
{
  Movie::Init(input);
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

void Comedy::Populate(std::istream& input)
{
  std::string title, year;
  std::getline(input, title, ',');
  input >> year;

  boost::algorithm::trim(title);
  boost::algorithm::trim(year);

  if(!input.fail()) {
    title_ = title;
    year_ = boost::lexical_cast<int>(year.c_str());
  }

  validate_input();
}

int Comedy::compare(const Comedy& lhs, const Comedy& rhs)
{
  int compare = lhs.title_.compare(rhs.title_);

  if(compare != 0)
    return compare;

  return lhs.year_ - rhs.year_;
}

// Sorted by title then date
bool Comedy::operator<(const Movie& other) const
{
  const Comedy& o = static_cast<const Comedy&>(other);

  if(Comedy::compare(*this, o) < 0)
    return true;
  else
    return false;
}

bool Comedy::operator>(const Movie& other) const
{
  const Comedy& o = static_cast<const Comedy&>(other);
  if(Comedy::compare(*this, o) > 0)
    return true;
  else
    return false;
}
