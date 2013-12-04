///////////////////////////////////////////////////////////////////////////////
// Movie.h
// Abstract base class that represents a movie and methods of reading data to
// populate its fields
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_MOVIE_H
#define CSS343_LAB4_MOVIE_H

#include <boost/functional/hash.hpp>

#include <iostream>
#include <string>

class Movie {

  // overloaded <<
  // Prints out the movie's director and title in table format
  friend std::ostream& operator<<(std::ostream&, const Movie&);

  public:
  // Default constructor
  // @param stream in the following format
  // format: "title  title,  director director, addtional data"
  //          string string, string   string  , string
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

  // Reads from the input stream and populates what fields it can. Then calls
  // parse_additional_data to read the rest
  //
  // @param stream in the following format
  // format: "title  title,  director director, addtional data"
  //          string string, string   string  , string
  virtual void Init(std::istream&);

  // Parses the istream and populates the movies methods according to the
  // movie's sorting criteria
  virtual void Populate(std::istream&) = 0;

  // Prints the table headers to view the movie data in a table format
  virtual void PrintTableHeader(std::ostream& = std::cout) const;

  // returns true if the left movie is less than the right movie
  // Uses the virtual compare function to determine movie order
  virtual bool operator<(const Movie&) const;
  virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;
  virtual bool operator!=(const Movie&) const;

  // returns a hash value that can be used to uniquely identify the movie
  // uses the virtual calculate_hash function to determine the has value
  static std::size_t hash(const Movie&);

  // getters
  std::string title() const;
  std::string director() const;
  int         year() const;

protected:
  std::string hash_value_; // default: director+title+year
  std::string title_; // the title of the movie
  std::string director_; // the director of the movie
  int year_; // the publishing date of the movie

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

  // prints out the object's fields in a table format
  virtual void print(std::ostream&) const;

  // Returns < 0 if this movie is less than the other movie
  // Returns > 0 if this movie is greater than the other movie
  // Returns 0 if this movie is equivalent to the other movie
  //
  // @param - the movie to compare to
  virtual int compare(const Movie&) const = 0;

  // calculates the hash value
  // default: boos::hash<std::string>(director+title) + year
  virtual std::size_t calculate_hash() const;

  static boost::hash<std::string> string_hash; // used to generate string hash
};

#endif
