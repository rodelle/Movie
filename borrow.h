///////////////////////////////////////////////////////////////////////////////
// Borrow.h
// Borrow is a derived class that inherits from transaction. It represents a
// customer borrowing a  movie from the store.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_BORROW_H
#define CSS343_LAB4_BORROW_H

#include "transaction.h"

class Borrow : public Transaction {
public:
  Borrow(Store&);
  virtual ~Borrow();

protected:
  // Performs the logic that needs to take place for a customer to
  // borrow a movie
  virtual bool commit_transaction();
};

#endif
