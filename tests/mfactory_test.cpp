#include <UnitTest++.h>
#include <iostream>

#include "../mfactory.h"
#include "../movie.h"
#include "../comedy.h"
#include "../drama.h"
#include "../classic.h"
#include "test_helper.h"

/*
// Test for bad cast exception when casting to references
struct ReferenceCastException 
{
  ReferenceCastException()
    : movie(NULL), comedy(NULL), drama(NULL)
  {
    MovieFactory factory;
    movie = factory.Create('f'); 
    comedy = dynamic_cast<Comedy*>(movie);
    drama = dynamic_cast<Drama*>(movie); 
  }

  ~ReferenceCastException()
  {
    if(movie != NULL)
      delete movie; 
  }

  Movie* movie;
  Comedy* comedy;
  Drama* drama;
};
*/

/*
// Generalize the process of casting each return vale to every other return value
struct MovieTypes 
{
  MovieTypes()
  {
    typedef std::pair<char, MovieCast> Pair;

    movie_types.insert(Pair('f', CastToComedy));
    movie_types.insert(Pair('d', CastToDrama));
    movie_types.insert(Pair('c', CastToClassic));
  }

  std::unordered_map<char, MovieCast> movie_types;
};
*/

SUITE(MFactory_h) 
{
  TEST(InstanceOf_default) 
  {
    MovieFactory factory;

    Movie* movie = factory.InstanceOf('f');
  
    Comedy* comedy = dynamic_cast<Comedy*>(movie);
    Drama* drama = dynamic_cast<Drama*>(movie);
    Classic* classic = dynamic_cast<Classic*>(movie);

    CHECK(movie != NULL);
    CHECK(comedy != NULL);
    CHECK(drama == NULL);
    CHECK(classic == NULL);
  }

  TEST(InstanceOf_nonexistent) 
  {
    MovieFactory factory;

    Movie* movie = factory.InstanceOf('x');
  
    Comedy* comedy = dynamic_cast<Comedy*>(movie);
    Drama* drama = dynamic_cast<Drama*>(movie);
    Classic* classic = dynamic_cast<Classic*>(movie);

    CHECK(movie == NULL);
    CHECK(comedy == NULL);
    CHECK(drama == NULL);
    CHECK(classic == NULL);
  }

  TEST(Create_nonexistent) 
  {
    MovieFactory factory;

    Movie* movie = factory.Create('x');
  
    Comedy* comedy = dynamic_cast<Comedy*>(movie);
    Drama* drama = dynamic_cast<Drama*>(movie);
    Classic* classic = dynamic_cast<Classic*>(movie);

    CHECK(movie == NULL);
    CHECK(comedy == NULL);
    CHECK(drama == NULL);
    CHECK(classic == NULL);
  }

  TEST(Create_drama) 
  {
    MovieFactory factory;

    Movie* movie = factory.Create('d');

    Comedy* comedy = dynamic_cast<Comedy*>(movie);
    Drama* drama = dynamic_cast<Drama*>(movie);
    Classic* classic = dynamic_cast<Classic*>(movie);

    CHECK(movie != NULL);
    CHECK(comedy == NULL);
    CHECK(drama != NULL);
    CHECK(classic == NULL);
  }

  TEST(Create_classic) 
  {
    MovieFactory factory;

    Movie* movie = factory.Create('c');

    Comedy* comedy = dynamic_cast<Comedy*>(movie);
    Drama* drama = dynamic_cast<Drama*>(movie);
    Classic* classic = dynamic_cast<Classic*>(movie);

    CHECK(movie != NULL);
    CHECK(comedy == NULL);
    CHECK(drama == NULL);
    CHECK(classic != NULL);
  }

  TEST(Create_comedy) 
  {
    MovieFactory factory;

    Movie* movie = factory.Create('f');

    Comedy* comedy = dynamic_cast<Comedy*>(movie);
    Drama* drama = dynamic_cast<Drama*>(movie);
    Classic* classic = dynamic_cast<Classic*>(movie);

    CHECK(movie != NULL);
    CHECK(comedy != NULL);
    CHECK(drama == NULL);
    CHECK(classic == NULL);
  }
}
