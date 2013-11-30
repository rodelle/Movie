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
    actor = data[0] + data[1];
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

// Prints the table headers to view the movie data in a table format
void Classic::PrintTableHeader()
{
  std::cout << std::left 
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR" 
    << std::setw(kMonthDisplayWidth) << "MONTH" 
    << std::setw(kYearDisplayWidth) << "YEAR" 
    << "MAJOR ACTOR"; 
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

// Sorted by date then famous actor 
bool Classic::operator<(const Movie& other) const
{
  int compare = 0;
  const Classic& o = static_cast<const Classic&>(other);
  
  compare = year_ - o.year_;
  
  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  compare = month_ - o.month_;

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  compare = actor_.compare(o.actor_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  return false; // equal to each other
}

bool Classic::operator>(const Movie& other) const
{
  return !((*this < other) || (*this == other)); 
}

bool Classic::operator==(const Movie& other) const
{
  const Classic& o = static_cast<const Classic&>(other);
  return (year_ == o.year_) 
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
