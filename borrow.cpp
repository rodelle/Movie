#include "borrow.h"
#include "store.h"
#include "scustomer.h"
#include "inventoryitem.h"

Borrow::Borrow(Store& store)
  : Transaction(store)
{
  name_ = "BORROW";
}

Borrow::~Borrow()
{}

bool Borrow::commit_transaction()
{
  if(item_->GetRemaining(mediatype_) <= 0) { // not enough movies exist
    std::cout << "** Error in Borrow: \"" << customer_->name()
      << "\" cannot checkout \"" << item_->movie().title() << "\". {"
      << item_->GetRemaining(mediatype_) << "} copies remain.\n";

    return false;
  }

  item_->RemoveFromInventory(1, mediatype_);
  customer_->CheckoutMovie(&(item_->movie()));
  customer_->AddTransaction(this);

  return true;
}
