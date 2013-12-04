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

  // override
  virtual void Populate(std::istream&);

private:
  virtual int compare(const Movie&) const;
};

#endif
