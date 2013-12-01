///////////////////////////////////////////////////////////////////////////////
// Rent.h
// Rent is a derived class that inherits from transaction. It represents a 
// customer borrowing a  movie from the store.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_RENT_H
#define CSS343_LAB4_RENT_H

#include "transaction.h"

class Rent : public Transaction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  Rent(StoreCustomer&, InventoryItem&);
  virtual ~Rent();

  // Performs the necessary operations to execute the transaction
  virtual bool ExecuteTransaction();
};

#endif
