#ifndef CSS343_LAB4_COMEDY_H
#define CSS343_LAB4_COMEDY_H

#include <string>
#include <istream>

#include "movie.h"

class Comedy: public Movie
{
// overloaded <<
// Prints out the movie's director and title in table format
friend std::ostream& operator<<(std::ostream&, const Comedy&);

public:
  //pre: 1800 <= year <= 2100
  //format: "title title, director director, year"
  Comedy(std::istream&);
  Comedy(
    const std::string& = kDefaultTitle,
    const std::string& = kDefaultDirector,
    const std::string& = kDefaultData);

  // override
  // @param input - stream of the format "title title, year"
  virtual void Populate(std::istream&);

  // copy ctors
  Comedy(const Comedy&);
  Comedy& operator=(Comedy);

  virtual ~Comedy();

  // returns true if the left movie is less than the right movie
  // Sorted by title then date
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

  static int compare(const Comedy&, const Comedy&);
};

#endif
