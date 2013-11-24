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
  Comedy(const std::string& = "", const std::string& = "", int year = 1900);
  
  // copy ctors
  Comedy(const Comedy&);
  Comedy& operator=(Comedy);

  virtual ~Comedy();

  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader();
    
  // returns true if the left movie is less than the right movie
  // Sorted by title then date 
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

};

#endif
