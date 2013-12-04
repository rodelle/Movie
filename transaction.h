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
  virtual bool ExecuteAction(std::istream&);

  const StoreCustomer& customer() const;
  const InventoryItem& item() const;

protected:
  // performs the actual transaction
  virtual bool commit_transaction() = 0;

  // populates customer and item using data from the store and parameters
  // from the stream
  virtual void initialize_data(std::istream&);

  StoreCustomer* customer_;
  InventoryItem* item_;
};

#endif
