#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap
#include <istream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "movie.h"

const int Movie::kTitleDisplayWidth = 22;
const int Movie::kDirectorDisplayWidth = 16;
const int Movie::kYearDisplayWidth = 5;

const int Movie::kMinYear = 1800;
const int Movie::kMaxYear = 2100;

const int Movie::kDefaultYear = Movie::kMinYear;

#ifdef NDEBUG
const std::string Movie::kDefaultTitle = "Title";
const std::string Movie::kDefaultDirector = "Director";
const std::string Moive::kDefaultData = "Data";
#else
const std::string Movie::kDefaultTitle = "";
const std::string Movie::kDefaultDirector = "";
const std::string Movie::kDefaultData = "";
#endif

Movie::Movie(std::istream& input)
{
  Movie::Init(input);
}

Movie::Movie(
  const std::string& title,
  const std::string& director,
  const std::string& data)
{
  Movie::Init(title, director, data);
}

void Movie::Init(
  const std::string& title,
  const std::string& director,
  const std::string& additional_data)
{
  title_ = title;
  director_ = director;
  parse_additional_data(additional_data);

  validate_input();
}

void Movie::parse_additional_data(const std::string& additional_data)
{
  try {
    year_ = boost::lexical_cast<int>(additional_data.c_str());
  } catch (const boost::bad_lexical_cast&) {
    year_ = kDefaultYear;
  }
}

void Movie::Init(std::istream& input)
{
  std::string title, director, additional_data;

  std::getline(input, director, ',');
  std::getline(input, title, ',');
  std::getline(input, additional_data);

  boost::algorithm::trim(title);
  boost::algorithm::trim(director);
  boost::algorithm::trim(additional_data);

  if(!input.fail()) {
    director_ = director;
    title_ = title;
    director_ = director;
    this->parse_additional_data(additional_data);
  }

  validate_input();
}

void Movie::validate_input()
{
  if(year_ < kMinYear)
    year_ = kMinYear;
  if(year_ > kMaxYear)
    year_ = kMaxYear;

  hash_value_ = director_ + title_;
}

// Prints the table headers to view the movie data in a table format
void Movie::PrintTableHeader(std::ostream& out) const
{
  out << std::left
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR"
    << std::setw(kYearDisplayWidth) << "YEAR";
}

std::ostream& operator<<(std::ostream& out, const Movie& movie)
{
  movie.print(out);
  return out;
}

void Movie::print(std::ostream& out) const
{
  out << std::left
    << std::setw(Movie::kTitleDisplayWidth)
    << title_.substr(0, kTitleDisplayWidth - 1)
    << std::setw(Movie::kDirectorDisplayWidth)
    << director_.substr(0, kDirectorDisplayWidth - 1)
    << std::setw(Movie::kYearDisplayWidth) << year_;
}

Movie::~Movie()
{

}

boost::hash<std::string> Movie::string_hash;

std::size_t Movie::hash(const Movie& movie)
{
  return movie.calculate_hash();
}

std::size_t Movie::calculate_hash() const
{
  return string_hash(hash_value_) + year_;
}

bool Movie::operator<(const Movie& other) const
{
  if(this->compare(other) < 0)
    return true;
  else
    return false;
}

bool Movie::operator>(const Movie& other) const
{
  if(this->compare(other) > 0)
    return true;
  else
    return false;
}

bool Movie::operator==(const Movie& other) const
{
  return (year_ == other.year_)
    && (director_.compare(other.director_) == 0)
    && (title_.compare(other.title_) == 0);
}

bool Movie::operator!=(const Movie& other) const
{
  return !(*this == other);
}

std::string Movie::title() const
{ return title_; }

std::string Movie::director() const
{ return director_; }

int Movie::year() const
{ return year_; }

