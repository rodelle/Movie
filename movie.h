#ifndef CSS343_LAB4_MOVIE_H
#define CSS343_LAB4_MOVIE_H

#include <string>

class Movie {
 
// overloaded <<
// Prints out the movie's director and title in table format 
friend std::ostream& operator<<(std::ostream&, const Movie&);

public:
  Movie(const std::string& = "", const std::string& = "");

  // copy ctors
  Movie(const Movie&);
  Movie& operator=(Movie);

  virtual ~Movie();

  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader();
    
  // returns true if the left movie is less than the right movie
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

private:
  std::string director_;
  std::string title_;
  //std::string date_;

  static const int kTitleDisplayWidth;
  static const int kDirectorDisplayWidth;
};

#endif
