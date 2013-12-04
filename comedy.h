///////////////////////////////////////////////////////////////////////////////
// Comedy.h
// a concrete class that inherits from the abstract Movie class, represents
// the comedy genre of movie
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_COMEDY_H
#define CSS343_LAB4_COMEDY_H

#include <istream>
#include <string>

#include "movie.h"

class Comedy: public Movie
{
// overloaded <<
// Prints out the movie's director and title in table format
friend std::ostream& operator<<(std::ostream&, const Comedy&);

public:
  // Default constructor
  // @param stream in the following format
  // format: "title  title, director director, year"
  //          string string string   string    int
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

private:
  // Returns < 0 if this movie is less than the other movie
  // Returns > 0 if this movie is greater than the other movie
  // Returns 0 if this movie is equivalent to the other movie
  // sorted by title then by date
  // @param - the movie to compare to
  virtual int compare(const Movie&) const;
};

#endif
