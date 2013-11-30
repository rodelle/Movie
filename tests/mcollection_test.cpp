#include <UnitTest++.h>
#include <iostream>

#include "../mcollection.h"
#include "../movie.h"
#include "test_helper.h"

struct MovieData
{
  MovieData()
  {
    SetData(
      data_pirates_of_the_caribbean, "F Gore Verbinski, Pirates of the Caribbean, 2003",
      search_pirates_of_the_caribbean, "D F Pirates of the Caribbean, 2003");

    SetData(
      data_schindlers_list,"D Steven Spielberg, Schindler's List, 1993",
      search_schindlers_list, "D Steven Spielberg, Schindler's List,");
  }

  std::istringstream data_pirates_of_the_caribbean;
  std::istringstream search_pirates_of_the_caribbean;

  std::istringstream data_schindlers_list;
  std::istringstream search_schindlers_list;

private:
  void SetData(
    std::istringstream& movie_data,
    const std::string& data_string,
    std::istringstream& search_data,
    const std::string& search_string) 
  {
    movie_data.str(data_string); 
    search_data.str(search_string); 
  }
  
};

SUITE(MCollection_h) 
{
  TEST_FIXTURE(MovieData, AddMovie_default) 
  {
    MovieCollection movies;
    movies.AddMovie(data_pirates_of_the_caribbean);

    InventoryItem* item = movies.GetMovie(search_pirates_of_the_caribbean);

    CHECK_EQUAL(10, item->GetInventoryCount('D'));
    CHECK_EQUAL("Pirates of the Caribbean", item->movie().title());
    CHECK_EQUAL("Gore Verbinski", item->movie().director());
    CHECK_EQUAL(2003, item->movie().year());
  }

  TEST_FIXTURE(MovieData, MultipleMovieTypes) 
  {
    MovieCollection movies;
    movies.AddMovie(data_pirates_of_the_caribbean);
    movies.AddMovie(data_schindlers_list);

    InventoryItem* item = movies.GetMovie(search_pirates_of_the_caribbean);

    CHECK_EQUAL(10, item->GetInventoryCount('D'));
    CHECK_EQUAL("Pirates of the Caribbean", item->movie().title());
    CHECK_EQUAL("Gore Verbinski", item->movie().director());
    CHECK_EQUAL(2003, item->movie().year());

    item = movies.GetMovie(search_schindlers_list);
    CHECK_EQUAL(10, item->GetInventoryCount('D'));
    CHECK_EQUAL("Schindler's List", item->movie().title());
    CHECK_EQUAL("Steven Spielberg", item->movie().director());
    CHECK_EQUAL(1993, item->movie().year());  }
}
