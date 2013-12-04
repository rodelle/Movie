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
  // Transactions can only exist between a Customer and a MovieItem
  Borrow(Store&);
  virtual ~Borrow();

protected:
  virtual bool commit_transaction();
};

#endif
