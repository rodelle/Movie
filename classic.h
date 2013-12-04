///////////////////////////////////////////////////////////////////////////////
// Classic.h
// a concrete class that inherits from the abstract Movie class, represents
// the classic genre of movie
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_CLASSIC_H
#define CSS343_LAB4_CLASSIC_H

#include <istream>
#include <string>

#include "movie.h"

class Classic: public Movie
{
// overloaded <<
// Prints out the movie's title, director, release year, release month, and
// famous actor in table format
friend std::ostream& operator<<(std::ostream&, const Classic&);

public:
  //format: "director director, title, actor  actor  month year"
  //         string   string    string string string int   int
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

  // Populates the fields needed to uniquely identify the movie
  //
  // @param input - stream with the following format
  // format: month  year  actor
  //         int    int   string
  virtual void Populate(std::istream&);

  // Returns true if both movies have the same director, title, year, month
  // and actor
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

  // getters
  int month() const;
  std::string actor() const;

protected:
  static const std::string kDefaultActor;
  static const int kDefaultMonth;
  static const int kMonthDisplayWidth;

  int month_; // number corresponding to the month the movie was released
  std::string actor_;

  // Validates that the years and months are within valid ranges
  // Calculates hash_value
  virtual void validate_input();

  // Reads in the actor, month, and year and populates the class' fields
  virtual void parse_additional_data(const std::string&);

  // Sorted by date then famous actor
  virtual int compare(const Movie&) const;

  // Prints out the movie information in a table format
  virtual void print(std::ostream&) const;

  // returns the hash value that uniquely identifies this movie
  virtual std::size_t calculate_hash() const;
};

#endif
