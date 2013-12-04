///////////////////////////////////////////////////////////////////////////////
// Return.h
// Return is a derived class that inherits from transaction. It represents a
// customer returning a previously checked out movie from the store.
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_RETURN_H
#define CSS343_LAB4_RETURN_H

#include "transaction.h"

class Movie;

class Return : public Transaction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  Return(Store&);
  virtual ~Return();

private:
  // performs the logic necessary for a customer to return a movie
  virtual bool commit_transaction();

  // Returns true if the user currently has the movie checked out
  // @param customer - the customer being queried
  // @param movie - the movie being searched for
  static bool user_has_movie(const StoreCustomer&, const Movie*);
};

#endif
