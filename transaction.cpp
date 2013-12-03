#include "scustomer.h"
#include "inventoryitem.h"
#include "transaction.h"

Transaction::Transaction(StoreCustomer& customer, InventoryItem& item)
  : customer_(customer), item_(item), isTransactionComplete_(false), name_("")
{}

Transaction::~Transaction()
{}

std::ostream& operator<<(std::ostream& out, const Transaction& transaction)
{
  out << InventoryItem::kDefaultMediaName
    << " " << transaction.name_
    << "  " << transaction.item_.movie();
  return out;
}

const std::string& Transaction::name() const
{ return name_; }
