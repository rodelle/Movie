#include <iomanip>
#include <iostream>

#include "showmovies.h"

#include "store.h"
#include "mcollection.h"

ShowMovies::ShowMovies(Store& store)
  : Action(store)
{}

ShowMovies::~ShowMovies()
{}

const int ShowMovies::kDvdCountDisplayWidth = 4;
const int ShowMovies::kMovieDisplayWidth = 71;

bool ShowMovies::ExecuteAction(std::istream& input)
{
  MovieCollection& movies = store_.movies();

  typedef MovieCollection::MovieSetHash MovieHash;
  typedef MovieCollection::MovieSet     MovieSet;

  MovieHash movie_hash = movies.GetAllMovies();
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

  return false;
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
  int remaining = item.GetRemaining();
  int total = item.GetTotal();

  std::cout << std::left
    << std::setw(kDvdCountDisplayWidth) << remaining
    << std::setw(kDvdCountDisplayWidth) << total - remaining
    << std::setw(kMovieDisplayWidth) << item.movie()
    << std::endl;
}
