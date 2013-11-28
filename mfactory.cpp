#include <tr1/unordered_map>
#include "mfactory.h"
#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"

MovieFactory::MovieFactory()
{
  typedef std::pair<char, MovieFactory::MovieBuilder> BuilderPair;

  movie_builder_.insert(BuilderPair('f', MovieFactory::MakeComedy));
  movie_builder_.insert(BuilderPair('d', MovieFactory::MakeDrama));
  movie_builder_.insert(BuilderPair('c', MovieFactory::MakeClassic));

  typedef std::pair<char, Movie*> MoviePair;

  movie_instance_.insert(MoviePair('f', MovieFactory::MakeComedy()));
  movie_instance_.insert(MoviePair('d', MovieFactory::MakeDrama()));
  movie_instance_.insert(MoviePair('c', MovieFactory::MakeClassic()));
}

MovieFactory::~MovieFactory()
{
  MovieHash::iterator i;
  for(i = movie_instance_.begin(); i != movie_instance_.end(); ++i) {
    delete i->second;
  }
}

Movie* MovieFactory::Create(const char movieType) const
{
  if(movie_builder_.count(movieType) == 1) {
    MovieBuilder movieBuilder = movie_builder_.find(movieType)->second;
    return movieBuilder();
  } 
  
  return NULL; // movie type does not exist
}

Movie* MovieFactory::InstanceOf(const char movieType) const
{
  if(movie_instance_.count(movieType) == 1)
    return movie_instance_.find(movieType)->second;
  
  return NULL; // movie type does not exist
}

Movie* MovieFactory::MakeComedy()
{ return new Comedy(); }

Movie* MovieFactory::MakeDrama()
{ return new Drama(); }

Movie* MovieFactory::MakeClassic()
{ return new Classic(); }

std::size_t MovieFactory::CharHash::operator() (const char c) const
{
  return c - 'a';
}
