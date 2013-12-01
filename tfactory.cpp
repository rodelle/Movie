#include <tr1/unordered_map>
#include "tfactory.h"
#include "transaction.h"
#include "borrow.h"
#include "return.h"

TransactionFactory::TransactionFactory()
{
  typedef std::pair<char, TransactionFactory::TransactionBuilder> Pair;

  transaction_builder_.insert(Pair('B', TransactionFactory::MakeBorrow));
  transaction_builder_.insert(Pair('R', TransactionFactory::MakeReturn));
}

TransactionFactory::~TransactionFactory()
{}

Transaction* TransactionFactory::Create(
  const char transactionType, 
  StoreCustomer& customer,
  InventoryItem& item) const
{
  if(transaction_builder_.count(transactionType) == 1) {
    TransactionBuilder builder = 
      transaction_builder_.find(transactionType)->second;
    return builder(customer, item);
  } 
  
  return NULL; // transaction type does not exist
}

Transaction* TransactionFactory::MakeBorrow(
  StoreCustomer& customer, 
  InventoryItem& item)
{ return new Borrow(customer, item); }

Transaction* TransactionFactory::MakeReturn(
  StoreCustomer& customer, 
  InventoryItem& item)
{ return new Return(customer, item); }

std::size_t TransactionFactory::CharHash::operator() (const char c) const
{
  return c - 'A';
}
