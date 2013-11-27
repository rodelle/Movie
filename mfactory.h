///////////////////////////////////////////////////////////////////////////////
// MovieFactory.h
// the MovieFactory class is used to instantiate objects of the Movie class. 
// It takes as input a char which represents the specific concrete movie class
// desired.  It uses a hash function to determine which object to create based
// on that char, then returns a pointer to that new movie object.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_MOVIEFACTORY_H
#define CSS343_LAB4_MOVIEFACTORY_H

#include <tr1/unordered_map>
#include "movie.h"

class MovieFactory 
{
public:
  // ctor should create (dynamically) one of each type of movie and store them in the 
  // movFactory array.
  MovieFactory();
  
  // Returns an instantiated Movie object of the correct type
  Movie* Create(const char) const;

private:
  static Movie* MakeComedy();
  static Movie* MakeDrama();
  static Movie* MakeClassic();

  struct CharHash
  {
    std::size_t operator() (const char) const;
  };

  static const int kNumMovieTypes;
  //typedef Movie* (MovieFactory::*MovieBuilder)();
  typedef Movie* (*MovieBuilder)();
  typedef std::tr1::unordered_map<char, MovieBuilder, CharHash> BuilderHash;
  BuilderHash movie_builder_; 
};

#endif
