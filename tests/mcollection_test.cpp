#include <UnitTest++.h>
#include <iostream>

#include "../mcollection.h"
#include "../movie.h"
#include "test_helper.h"

SUITE(MCollection_h) 
{
  TEST(AddMovie_default) 
  {
    std::string movie_data = "F Gore Verbinski, Pirates of the Caribbean, 2003";
    std::string search_data = "D F Pirates of the Caribbean, 2003";

    std::istringstream movie_data_stream(movie_data);
    std::istringstream search_data_stream(search_data);
  
    MovieCollection movies;
    movies.AddMovie(movie_data_stream);

    InventoryItem* item = movies.GetMovie(search_data_stream);

    CHECK_EQUAL(10, item->GetInventoryCount('D'));
    CHECK_EQUAL("Pirates of the Caribbean", item->movie().title());
    CHECK_EQUAL("Gore Verbinski", item->movie().director());
    CHECK_EQUAL(2003, item->movie().year());
  }
/*
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
*/
}
