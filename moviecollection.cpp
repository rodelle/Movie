#include <set>
#include <vector>
#include <iostream>
#include "movie.h"
#include "comedy.h"
struct MovieCompare 
{
  bool operator() (const Movie& lhs, const Movie& rhs) const
  {
    return lhs < rhs;
  }
};

class MovieCollection 
{
public:
  typedef std::set<Movie&, MovieCompare> MovieSet;
  MovieCollection()
  {
    collection_.insert(Comedy("Jello", "Bob Dole", 1997));
    for(MovieSet::iterator i = collection_.begin(); i != collection_.end(); ++i)
    {
      std::cout << *i;
    }
    
  }

  MovieSet collection_; 
};

int main()
{
  MovieCollection a; 
  return 0;
}
