#ifndef CSS343_LAB4_MOVIE_H
#define CSS343_LAB4_MOVIE_H

#include <string>
#include <istream>

class Movie {
 
// overloaded <<
// Prints out the movie's director and title in table format 
friend std::ostream& operator<<(std::ostream&, const Movie&);

public:
  Movie(std::istream&);
  Movie(
    const std::string& = kDefaultTitle,
    const std::string& = kDefaultDirector, 
    const std::string& = kDefaultData);
  
  virtual ~Movie();

  //format: "title title, director director, year"
  virtual void Init(
    const std::string& = kDefaultTitle,
    const std::string& = kDefaultDirector, 
    const std::string& = kDefaultData);

  virtual void Init(std::istream&);

  // Parses the istream and populates the movies methods according to the
  // movie's sorting criteria
  virtual void Populate(std::istream&) = 0;
  
  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader();
    
  // returns true if the left movie is less than the right movie
  // Sorted by title then director
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

  // getters
  std::string title() const;
  std::string director() const;
  int         year() const;

protected:
  std::string title_;
  std::string director_;
  int year_; 

  static const int kTitleDisplayWidth;
  static const int kDirectorDisplayWidth;
  static const int kYearDisplayWidth;

  static const int kMinYear;
  static const int kMaxYear;
  
  static const int kDefaultYear;
  static const std::string kDefaultTitle;
  static const std::string kDefaultDirector;
  static const std::string kDefaultData;

  // Checks to make sure values are within valid ranges 
  // If they aren't, sets them to default values
  virtual void validate_input();

  // parses the additional data field and initializes corresponding fields 
  virtual void parse_additional_data(const std::string&);
};

#endif
