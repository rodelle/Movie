#ifndef CSS343_LAB4_DRAMA_H_
#define CSS343_LAB4_DRAMA_H

#include <string>
#include <istream>

#include "movie.h"

// Drama.h
// a concrete class that inherits from the abstract Movie class, represents 
// the drama genre of movie
class Drama : public Movie 
{
// overloaded <<
// Prints out the movie's director and title in table format 
friend std::ostream& operator<<(std::ostream&, const Drama&);

public:
  //pre: 1800 <= year <= 2100 
  //format: "title title, director director, year"
  Drama(std::istream&);
  Drama(const std::string& = kDefaultTitle,
        const std::string& = kDefaultDirector,
        const std::string& = kDefaultData);
  
  // copy ctors
  Drama(const Drama&);
  Drama& operator=(Drama);

  virtual ~Drama();

  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader();

  // override
  virtual void Populate(std::istream&);

  // returns true if the left movie is less than the right movie
  // Sorted by director then title 
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;
};

#endif
