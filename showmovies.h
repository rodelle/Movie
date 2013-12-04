///////////////////////////////////////////////////////////////////////////////
// ShowMovies.h
// Allows the store to display the current stock of all movies sorted by their
// categories and then by their respective sorting criteria.
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_SHOWMOVIES_H
#define CSS343_LAB4_SHOWMOVIES_H

#include "action.h"

class Store;
class InventoryItem;

class ShowMovies : public Action {
public:
  // Transactions can only exist between a Customer and a MovieItem
  ShowMovies(Store&);
  virtual ~ShowMovies();

  // performs the action of retreiving and printing the list of movies
  // that the store owns
  virtual bool ExecuteAction(std::istream&);

private:
  static const int kDvdCountDisplayWidth;
  static const int kMovieDisplayWidth;
  void print_movie_info(const InventoryItem&) const;
  void print_table_header(const InventoryItem&) const;
};

#endif
