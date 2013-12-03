///////////////////////////////////////////////////////////////////////////////
// TransactionFactory.h
// The TransactionFactory class is used to instantiate objects of the Transaction class. 
// It takes as input a char which represents the specific concrete movie class
// desired.  It uses a hash function to determine which object to create based
// on that char, then returns a pointer to that new movie object.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_TRANSACTIONFACTORY_H
#define CSS343_LAB4_TRANSACTIONFACTORY_H

#include <tr1/unordered_map>

class InventoryItem;
class StoreCustomer;
class Transaction;

class TransactionFactory 
{
public:
  TransactionFactory();
  ~TransactionFactory();
  
  // Returns an instantiated Transaction object of the correct type
  Transaction* Create(const char, StoreCustomer&, InventoryItem&) const;

private:
  static Transaction* MakeBorrow(StoreCustomer&, InventoryItem&);
  static Transaction* MakeReturn(StoreCustomer&, InventoryItem&);

  struct CharHash
  {
    std::size_t operator() (const char) const;
  };

  static const int kNumTransactionTypes;
  typedef Transaction* (*TransactionBuilder)(StoreCustomer&, InventoryItem&);
  typedef std::tr1::unordered_map<char, TransactionBuilder, CharHash> BuilderHash;
  typedef std::tr1::unordered_map<char, Transaction*, CharHash> TransactionHash;

  BuilderHash transaction_builder_; // hash of functions to create new movies
  TransactionHash transaction_instance_; // hash of a single movie instance 
};

#endif
