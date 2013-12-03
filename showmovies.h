///////////////////////////////////////////////////////////////////////////////
// ShowMovies.h
// Allows the store to display the current stock of all movies sorted by their
// categories and then by their respective sorting criteria.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_SHOWMOVIES_H
#define CSS343_LAB4_SHOWMOVIES_H

#include "saction.h"

class StoreCustomer;
class MovieCollection;
class InventoryItem;

class ShowMovies : public StoreAction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  ShowMovies();
  virtual ~ShowMovies();

  // Does nothing
  virtual void ExecuteAction(const StoreCustomer&);

  // Performs the necessary operations to execute the action 
  virtual void ExecuteAction(const MovieCollection&);
private:
  static const int kDvdCountDisplayWidth;
  static const int kMovieDisplayWidth;
  void print_movie_info(const InventoryItem&) const;
  void print_table_header(const InventoryItem&) const;
};

#endif
