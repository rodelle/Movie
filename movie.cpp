#include <iomanip>
#include <iostream>
#include <algorithm> // std::swap

#include "movie.h"
 
const int Movie::kTitleDisplayWidth = 20;
const int Movie::kDirectorDisplayWidth = 15;

Movie::Movie(const std::string& title, const std::string& director)
  : director_(director), title_(title)
{
}

std::ostream& operator<<(std::ostream& out, const Movie& movie)
{
  out << std::left 
    << std::setw(Movie::kTitleDisplayWidth) << movie.title_
    << std::setw(Movie::kDirectorDisplayWidth) << movie.director_; 

 return out;
}

Movie::Movie(const Movie& other)
{
  director_ = other.director_;
  title_ = other.title_;
}

Movie::~Movie()
{

}

Movie& Movie::operator=(Movie other)
{
  std::swap(director_, other.director_);
  std::swap(title_, other.title_);
  return *this;
}

// Prints the table headers to view the movie data in a table format
void Movie::PrintTableHeader()
{
  std::cout << std::left 
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR"; 
}

// Sorted by title then director
bool Movie::operator<(const Movie& other) const
{
  int compare = 0;
  compare = title_.compare(other.title_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;
  
  compare = director_.compare(other.director_);

  if(compare < 0)
    return true;
  else if(compare > 0)
    return false;

  return false; // equal to each other
}

bool Movie::operator>(const Movie& other) const
{
  return !(*this < other); 
}

bool Movie::operator==(const Movie& other) const
{
  return (director_.compare(other.director_) == 0)
      && (title_.compare(other.title_) == 0);
}

bool Movie::operator!=(const Movie& other) const
{
  return !(*this == other);
}
