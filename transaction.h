///////////////////////////////////////////////////////////////////////////////
// Transaction.h
// Transaction is a base class from which the different concrete types of
// derived transactions inherit. Each transaction represents an association
// between a customer and an inventoryitem
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_TRANSACTION_H
#define CSS343_LAB4_TRANSACTION_H

#include <string>
#include "action.h"

class StoreCustomer;
class InventoryItem;

class Transaction : public Action {
friend std::ostream& operator<<(std::ostream&, const Transaction&);
public:
  // Transactions can only exist between a Customer and a MovieItem
  Transaction(Store&);
  virtual ~Transaction();

  // Performs the necessary operations to execute the transaction
  virtual bool ExecuteAction(std::istream&) = 0;

  virtual const std::string& name() const;

protected:
  StoreCustomer* customer_;
  InventoryItem* item_;
};

#endif
