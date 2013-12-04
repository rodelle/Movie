///////////////////////////////////////////////////////////////////////////////
// Drama.h
// a concrete class that inherits from the abstract Movie class, represents
// the drama genre of movie
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_DRAMA_H_
#define CSS343_LAB4_DRAMA_H

#include <istream>
#include <string>

#include "movie.h"

class Drama : public Movie
{
  // overloaded <<
  // Prints out the movie's director and title in table format
  friend std::ostream& operator<<(std::ostream&, const Drama&);

public:
  // Default constructor
  // @param stream in the following format
  // format: "title  title, director director, year"
  //          string string string   string    int
  Drama(std::istream&);
  Drama(const std::string& = kDefaultTitle,
      const std::string& = kDefaultDirector,
      const std::string& = kDefaultData);

  // copy ctors
  Drama(const Drama&);
  Drama& operator=(Drama);

  virtual ~Drama();

  // Populates the fields needed to uniquely identify the movie
  //
  // @param input - stream with the following format
  // format: title, year
  //         string int
  virtual void Populate(std::istream&);

private:
  // Sorts the movies by director then by title
  //
  // Returns < 0 if this movie is less than the other movie
  // Returns > 0 if this movie is greater than the other movie
  // Returns 0 if this movie is equivalent to the other movie
  //
  // @param - the movie to compare to
  virtual int compare(const Movie&) const;
};

#endif
