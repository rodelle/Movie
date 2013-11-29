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
  virtual void PrintTableHeader();

  // override
  virtual void Populate(std::istream&);
    
  // returns true if the left movie is less than the right movie
  // Sorted by date then famous actor
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

protected:
  static const int kDefaultMonth;
  static const int kMonthDisplayWidth;
  static const std::string kDefaultActor;

  int month_; // number corresponding to the month the movie was released
  std::string actor_;

  // override
  virtual void validate_input();

  // override
  virtual void parse_additional_data(const std::string&);
};

#endif
