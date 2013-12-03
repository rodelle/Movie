#include "borrow.h"
#include "scustomer.h"
#include "inventoryitem.h"

Borrow::Borrow(Store& store)
  : Transaction(store)
{
  name_ = "BORROW";
}

Borrow::~Borrow()
{}

bool Borrow::ExecuteAction(std::istream& input)
{
  if(isTransactionComplete_) // transactions can only occur once
    return false;

  if(item_.GetInventoryCount() <= 0) // not enough movies exist
    return false;

  item_.RemoveFromInventory(1);
  customer_.CheckoutMovie(&item_.movie());
  customer_.AddTransaction(this);
  isTransactionComplete_ = true;

  return true;
}
