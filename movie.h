#ifndef CSS343_LAB4_MOVIE_H
#define CSS343_LAB4_MOVIE_H

#include <string>
#include <istream>

class Movie {
 
// overloaded <<
// Prints out the movie's director and title in table format 
friend std::ostream& operator<<(std::ostream&, const Movie&);

public:
  //pre: 1800 <= year <= 2100 
  //format: "title title, director director, year"
  Movie(std::istream&);
  Movie(const std::string& = "", const std::string& = "", int year = 1900);

  // copy ctors
  Movie(const Movie&);
  Movie& operator=(Movie);

  virtual ~Movie();

  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader();
    
  // returns true if the left movie is less than the right movie
  // Sorted by title then director
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

protected:
  std::string title_;
  std::string director_;
  int year_; 

  static const int kTitleDisplayWidth;
  static const int kDirectorDisplayWidth;
  static const int kYearDisplayWidth;

  static const int kMinYear;
  static const int kMaxYear;

  // Checks to make sure values are within valid ranges 
  // If they aren't, sets them to default values
  void validate_input();
};

#endif
