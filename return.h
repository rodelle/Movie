///////////////////////////////////////////////////////////////////////////////
// Return.h
// Return is a derived class that inherits from transaction. It represents a
// customer returning a previously checked out movie from the store.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_RETURN_H
#define CSS343_LAB4_RETURn_H

#include "transaction.h"

class Movie;

class Return : public Transaction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  Return(Store&);
  virtual ~Return();

  // Performs the necessary operations to execute the transaction
  virtual bool ExecuteAction(std::istream&);

private:
  static bool user_has_movie(const StoreCustomer&, const Movie*);
};

#endif
