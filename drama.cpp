#include <algorithm> // std::swap
#include <iomanip>
#include <iostream>
#include <istream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "drama.h"

Drama::Drama(
  const std::string& title,
  const std::string& director,
  const std::string& data)
{
  Movie::Init(title, director, data);
}

Drama::Drama(std::istream& input)
{
  Movie::Init(input);
}

std::ostream& operator<<(std::ostream& out, const Drama& movie)
{
  movie.print(out);
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

// format "title, director,"
void Drama::Populate(std::istream& input)
{
  std::string title, director;

  std::getline(input, director, ',');
  std::getline(input, title, ',');

  boost::algorithm::trim(director);
  boost::algorithm::trim(title);

  if(!input.fail()) {
    title_ = title;
    director_ = director;
  }

  validate_input();
}

// Ssrted by director then title
int Drama::compare(const Movie& other) const
{
  const Drama& o = static_cast<const Drama&>(other);
  int compare = director_.compare(o.director_);

  if(compare != 0)
    return compare;

  return title_.compare(o.title_);
}
