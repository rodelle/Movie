///////////////////////////////////////////////////////////////////////////////
// Transaction.h
// Transaction is a base class from which the different concrete types of 
// derived transactions inherit. Each transaction represents an association
// between a customer and an inventoryitem
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_TRANSACTION_H
#define CSS343_LAB4_TRANSACTION_H

class StoreCustomer;
class InventoryItem;

class Transaction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  Transaction(StoreCustomer&, InventoryItem&);
  virtual ~Transaction();

  // Performs the necessary operations to execute the transaction
  virtual void ExecuteTransaction() = 0;

private:
  StoreCustomer& customer_;
  InventoryItem& item_;
};

#endif
