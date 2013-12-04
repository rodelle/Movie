#ifndef CSS343_LAB4_CLASSIC_H
#define CSS343_LAB4_CLASSIC_H

#include <string>
#include <istream>

#include "movie.h"


// a concrete class that inherits from the abstract Movie class, represents
// the classic genre of movie
class Classic: public Movie
{
// overloaded <<
// Prints out the movie's title, director, release year, release month, and
// famous actor in table format
friend std::ostream& operator<<(std::ostream&, const Classic&);

public:
  //pre: 1900 <= year <= 2100
  //format: "title title, director director, year"
  Classic(std::istream&);
  Classic(
    const std::string& = kDefaultTitle,
    const std::string& = kDefaultDirector,
    const std::string& = kDefaultData);

  // copy ctors
  Classic(const Classic&);
  Classic& operator=(Classic);

  virtual ~Classic();

  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader(std::ostream& = std::cout) const;

  // override
  virtual void Populate(std::istream&);

  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

  // getters
  int month() const;
  std::string actor() const;

protected:
  static const int kDefaultMonth;
  static const int kMonthDisplayWidth;
  static const std::string kDefaultActor;

  int month_; // number corresponding to the month the movie was released
  std::string actor_;

  virtual void validate_input();
  virtual void parse_additional_data(const std::string&);

  // Sorted by date then famous actor
  virtual int compare(const Movie&) const;
  virtual void print(std::ostream&) const;

  virtual std::size_t calculate_hash() const;
};

#endif
