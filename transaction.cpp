#include "action.h"
#include "inventoryitem.h"
#include "ccollection.h"
#include "mcollection.h"
#include "scustomer.h"
#include "store.h"
#include "transaction.h"

Transaction::Transaction(Store& store)
  : Action(store)
{}

Transaction::~Transaction()
{}

std::ostream& operator<<(std::ostream& out, const Transaction& transaction)
{
  out << InventoryItem::kDefaultMediaName
    << " " << transaction.name_
    << "  " << transaction.item_->movie();
  return out;
}

bool Transaction::ExecuteAction(std::istream& input)
{
  if(isActionComplete_) // transactions can only occur once
    return false;

  initialize_data(input);

  if(item_ == NULL || customer_ == NULL)
    return false; // transaction cannot be completed

  if(item_->GetRemaining() <= 0) // not enough movies exist
    return false;

  isActionComplete_ = this->commit_transaction();
  return isActionComplete_;
}

// format customer_id, media type, movie search parameters
void Transaction::initialize_data(std::istream& input)
{
  int customer_id;
  char media_type;
  input >> customer_id >> media_type;
  input.get(); // ignore the blank character

  CustomerCollection& customers = store_.customers();
  MovieCollection& movies = store_.movies();

  customer_ = customers.GetCustomer(customer_id);
  item_ = movies.GetMovie(input);
}

const StoreCustomer& Transaction::customer() const
{ return *customer_; }

const InventoryItem& Transaction::item() const
{ return *item_; }
