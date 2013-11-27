#include <tr1/unordered_map>
#include "mfactory.h"
#include "movie.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"

MovieFactory::MovieFactory()
{
  typedef std::pair<char, MovieFactory::MovieBuilder> Pair;

  movie_builder_.insert(Pair('f', MovieFactory::MakeComedy));
  movie_builder_.insert(Pair('d', MovieFactory::MakeDrama));
  movie_builder_.insert(Pair('c', MovieFactory::MakeClassic));
}

Movie* MovieFactory::Create(const char movieType) const
{
  if(movie_builder_.count(movieType) == 1) {
    MovieBuilder movieBuilder = movie_builder_.find(movieType)->second;
    return movieBuilder();
  } 
  
  return NULL; // movie type does not exist
}

Movie* MovieFactory::MakeComedy()
{ return new Comedy("Comedy"); }

Movie* MovieFactory::MakeDrama()
{ return new Drama("Drama"); }

Movie* MovieFactory::MakeClassic()
{ return new Classic("Classic"); }

std::size_t MovieFactory::CharHash::operator() (const char c) const
{
  return c - 'a';
}

#include <iostream>

int main()
{
  MovieFactory factory;
  Movie* movie = factory.Create('f');
  std::cout << *movie << std::endl;
  delete movie;
  movie = factory.Create('c');
  std::cout << *movie << std::endl;
  delete movie;
  movie = factory.Create('d');
  std::cout << *movie << std::endl;
}
