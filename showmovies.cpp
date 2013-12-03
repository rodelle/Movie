#include <iomanip>
#include <iostream>

#include "showmovies.h"
#include "scustomer.h"
#include "mcollection.h"

ShowMovies::ShowMovies()
{}

ShowMovies::~ShowMovies()
{}

void ShowMovies::ExecuteAction(const StoreCustomer& movies)
{}

const int ShowMovies::kDvdCountDisplayWidth = 4;
const int ShowMovies::kMovieDisplayWidth = 71;

void ShowMovies::ExecuteAction(const MovieCollection& movie_collection)
{
  typedef MovieCollection::MovieSetHash MovieHash;
  typedef MovieCollection::MovieSet     MovieSet;

  MovieHash movie_hash = movie_collection.GetAllMovies();
  MovieHash::const_iterator movie_set = movie_hash.begin();

  // iterate over the different movie types. eg. Comedy, Drama, Classic
  for(; movie_set != movie_hash.end(); ++movie_set) {
    MovieSet::const_iterator movie = movie_set->second.begin();
    
    if(movie != movie_set->second.end()) {
      print_table_header(**movie);
     }

    // iterate over each movie in the sets
    for(; movie != movie_set->second.end(); ++movie) {
      print_movie_info(**movie);     
    }
    std::cout << std::endl;
  }
}

void ShowMovies::print_table_header(const InventoryItem& item) const
{
  std::cout << std::left
    << std::setw(kDvdCountDisplayWidth) << "IN" 
    << std::setw(kDvdCountDisplayWidth) << "OUT" 
    << std::setw(kMovieDisplayWidth);

  item.movie().PrintTableHeader();
  
  std::cout << std::endl;

}

void ShowMovies::print_movie_info(const InventoryItem& item) const
{
  std::cout << std::left
    << std::setw(kDvdCountDisplayWidth) << item.GetInventoryCount() 
    << std::setw(kDvdCountDisplayWidth) << 5 
    << std::setw(kMovieDisplayWidth) << item.movie()
    << std::endl;
}
