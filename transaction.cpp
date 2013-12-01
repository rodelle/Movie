#include "scustomer.h"
#include "inventoryitem.h"
#include "transaction.h"

Transaction::Transaction(StoreCustomer& customer, InventoryItem& item)
  : customer_(customer), item_(item), isTransactionComplete_(false)
{}

Transaction::~Transaction()
{}
