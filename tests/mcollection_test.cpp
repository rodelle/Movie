#include <UnitTest++.h>
#include <iostream>

#include "../mcollection.h"
#include "../movie.h"
#include "test_helper.h"

struct MovieCollectionMovieData
{
  MovieCollectionMovieData()
  {
    SetData(
      data_pirates_of_the_caribbean, "F Gore Verbinski, Pirates of the Caribbean, 2003",
      search_pirates_of_the_caribbean, "D F Pirates of the Caribbean, 2003");

    SetData(
      data_schindlers_list,"D Steven Spielberg, Schindler's List, 1993",
      search_schindlers_list, "D D Steven Spielberg, Schindler's List,");

    SetData(
      data_holiday_khepburn, "C George Cukor, Holiday, Katherine Hepburn 9 1938",
      search_holiday_khepburn, "D C 9 1938 Katherine Hepburn");

    SetData(
      data_holiday_cgrant, "C George Cukor, Holiday, Cary Grant 9 1938",
      search_holiday_cgrant, "D C 9 1938 Cary Grant");
  }

  std::istringstream data_pirates_of_the_caribbean;
  std::istringstream search_pirates_of_the_caribbean;

  std::istringstream data_schindlers_list;
  std::istringstream search_schindlers_list;

  std::istringstream data_holiday_khepburn;
  std::istringstream data_holiday_cgrant;
  std::istringstream search_holiday_khepburn;
  std::istringstream search_holiday_cgrant;

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
  TEST_FIXTURE(MovieCollectionMovieData, AddMovie_default) 
  {
    MovieCollection movies;
    movies.AddMovie(data_pirates_of_the_caribbean);

    InventoryItem* item = movies.GetMovie(search_pirates_of_the_caribbean);

    CHECK_EQUAL(10, item->GetInventoryCount('D'));
    CHECK_EQUAL("Pirates of the Caribbean", item->movie().title());
    CHECK_EQUAL("Gore Verbinski", item->movie().director());
    CHECK_EQUAL(2003, item->movie().year());
  }

  TEST_FIXTURE(MovieCollectionMovieData, MultipleMovieTypes) 
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
    CHECK_EQUAL(1993, item->movie().year());  
  }

  TEST_FIXTURE(MovieCollectionMovieData, SameHashDifferentSortCriteria) 
  {
    MovieCollection movies;
    movies.AddMovie(data_holiday_khepburn);

    InventoryItem* item = movies.GetMovie(search_holiday_khepburn);

    CHECK_EQUAL(10, item->GetInventoryCount('D'));
    CHECK_EQUAL("Holiday", item->movie().title());
    CHECK_EQUAL("George Cukor", item->movie().director());
    CHECK_EQUAL(1938, item->movie().year());

    movies.AddMovie(data_holiday_cgrant);
    item = movies.GetMovie(search_holiday_cgrant);
    
/*
    CHECK(item != NULL);
    CHECK_EQUAL(20, item->GetInventoryCount('D'));
    CHECK_EQUAL("Holiday", item->movie().title());
    CHECK_EQUAL("George Cukor", item->movie().director());
    CHECK_EQUAL(1938, item->movie().year());
*/
  }
}
