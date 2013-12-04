#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap
#include <istream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include "classic.h"

const int Classic::kMonthDisplayWidth = 2;

const int Classic::kDefaultMonth = 1;
const std::string Classic::kDefaultActor = "";

Classic::Classic(
  const std::string& title,
  const std::string& director,
  const std::string& data)
  : month_(kDefaultMonth)
{
  Movie::Init(title, director, data);
}

Classic::Classic(std::istream& input)
{
  Movie::Init(input);
}

void Classic::validate_input()
{
  Movie::validate_input();
  if(month_ < 1 || month_ > 12)
   month_ = kDefaultMonth;

  hash_value_ = director_ + title_ + actor_;
}

std::size_t Classic::calculate_hash() const
{
  return Movie::string_hash(hash_value_) + year_ + month_;
}
void Classic::parse_additional_data(const std::string& additional_data)
{
  boost::tokenizer<> tok(additional_data);
  std::vector<std::string> data;

  // copy tokens into vector
  std::copy(tok.begin(), tok.end(),
      std::back_inserter<std::vector<std::string> >(data));

  if(data.size() == 4) {
    // format: actor, actor, month, year
    std::string actor, month, year;
    actor = data[0] + " " +  data[1];
    month = data[2];
    year  = data[3];

    actor_ = actor;

    try {
      month_ = boost::lexical_cast<int>(month.c_str());
      year_ = boost::lexical_cast<int>(year.c_str());
    } catch (const boost::bad_lexical_cast&) {
      month_ = kDefaultMonth;
      year_ = kDefaultYear;
    }
  }
}

// Prints the table headers to view the movie data in a table format
void Classic::PrintTableHeader(std::ostream& out) const
{
  out << std::left
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR"
    << std::setw(kMonthDisplayWidth) << "MO "
    << std::setw(kYearDisplayWidth) << "YEAR"
    << "MAJOR ACTOR";
}

std::ostream& operator<<(std::ostream& out, const Classic& movie)
{
  out << std::left
    << std::setw(Classic::kTitleDisplayWidth) << movie.title_
    << std::setw(Classic::kDirectorDisplayWidth) << movie.director_
    << std::setw(Classic::kMonthDisplayWidth) << movie.month_
    << std::setw(Classic::kYearDisplayWidth) << movie.year_
    << movie.actor_;

 return out;
}

Classic::Classic(const Classic& other)
{
  director_ = other.director_;
  title_ = other.title_;
  actor_ = other.actor_;
  month_ = other.month_;
  year_ = other.year_;
}

Classic::~Classic()
{

}

Classic& Classic::operator=(Classic other)
{
  std::swap(director_, other.director_);
  std::swap(title_, other.title_);
  std::swap(actor_, other.actor_);
  std::swap(month_, other.month_);
  std::swap(year_, other.year_);
  return *this;
}

void Classic::Populate(std::istream& input)
{
  std::string month, year, actor;

  input >> month;
  input >> year;
  std::getline(input, actor);

  boost::algorithm::trim(month);
  boost::algorithm::trim(year);
  boost::algorithm::trim(actor);

  if(!input.fail()) {
    actor_ = actor;
    month_ = boost::lexical_cast<int>(month.c_str());
    year_ = boost::lexical_cast<int>(year.c_str());
  }

  validate_input();
}

// Sorted by year, month, then famous actor
int Classic::compare(const Movie& other) const
{
  const Classic& o = static_cast<const Classic&>(other);
  if(year_ - o.year_ != 0)
    return year_ - o.year_;

  else if(month_ - o.month_ != 0)
    return month_ - o.month_;

  else
    return actor_.compare(o.actor_);
}

bool Classic::operator==(const Movie& other) const
{
  const Classic& o = static_cast<const Classic&>(other);
  return (year_ == o.year_)
    && (month_ == o.month_)
    && (actor_.compare(o.actor_) == 0)
    && (director_.compare(o.director_) == 0)
    && (title_.compare(o.title_) == 0);
}

bool Classic::operator!=(const Movie& other) const
{
  return !(*this == other);
}

std::string Classic::actor() const
{ return actor_; }

int Classic::month() const
{ return month_; }

void Classic::print(std::ostream& out) const
{
  Movie::print(out);
  out << std::right
    << std::setw(Classic::kMonthDisplayWidth) << month_ << " "
    << std::left
    << std::setw(Classic::kYearDisplayWidth) << year_
    << actor_;
}
