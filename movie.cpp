#include <iomanip>
#include <iostream>

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

}

Movie::~Movie()
{

}

Movie& Movie::operator=(Movie other)
{
  return *this;
}

// Prints the table headers to view the movie data in a table format
void Movie::PrintTableHeader()
{
  std::cout << std::left 
    << std::setw(kTitleDisplayWidth) << "TITLE"
    << std::setw(kDirectorDisplayWidth) << "DIRECTOR"; 
}

// returns true if the left movie is less than the right movie
bool Movie::operator<(const Movie& other) const
{
  return true;
}

bool Movie::operator>(const Movie& other) const
{
  return true;
}

bool Movie::operator==(const Movie& other) const
{
  return true;
}

bool Movie::operator!=(const Movie& other) const
{
  return true;
}
