///////////////////////////////////////////////////////////////////////////////
// MovieFactory.h
// the MovieFactory class is used to instantiate objects of the Movie class.
// It takes as input a char which represents the specific concrete movie class
// desired.  It uses a hash function to determine which object to create based
// on that char, then returns a pointer to that new movie object.
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_MOVIEFACTORY_H
#define CSS343_LAB4_MOVIEFACTORY_H

#include <tr1/unordered_map>
#include "movie.h"

class MovieFactory
{
public:
  // ctor should create (dynamically) one of each type of movie and store
  // them in the movieFactory array.
  MovieFactory();
  ~MovieFactory();

  // Returns an instantiated Movie object of the correct type
  Movie* Create(const char) const;

  // Returns a previously instantiated Movie object of the correct type
  // TODO prevent users from deleting this value
  Movie* InstanceOf(const char) const;

private:
  static Movie* MakeComedy();
  static Movie* MakeDrama();
  static Movie* MakeClassic();

  struct CharHash
  {
    std::size_t operator() (const char) const;
  };

  static const int kNumMovieTypes;
  typedef Movie* (*MovieBuilder)();
  typedef std::tr1::unordered_map<char, MovieBuilder, CharHash> BuilderHash;
  typedef std::tr1::unordered_map<char, Movie*, CharHash> MovieHash;

  BuilderHash movie_builder_; // hash of functions to create new movies
  MovieHash movie_instance_; // hash of a single movie instance
};

#endif
