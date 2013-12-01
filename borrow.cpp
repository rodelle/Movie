#include "borrow.h"
#include "scustomer.h"
#include "inventoryitem.h"

Borrow::Borrow(StoreCustomer& customer, InventoryItem& item)
  : Transaction(customer, item) 
{}

Borrow::~Borrow()
{}

bool Borrow::ExecuteTransaction()
{
  if(isTransactionComplete_) // transactions can only occur once
    return false; 
  
  if(item_.GetInventoryCount() <= 0) // not enough movies exist
    return false;

  item_.RemoveFromInventory(1);
  customer_.CheckoutMovie(&item_.movie()); 
  isTransactionComplete_ = true;

  return true;
}
