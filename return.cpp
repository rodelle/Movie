#include <algorithm>
#include "return.h"
#include "scustomer.h"
#include "inventoryitem.h"

Return::Return(Store& store)
  : Transaction(store)
{
  name_ = "RETURN";
}

Return::~Return()
{}

bool Return::ExecuteAction(std::istream& input)
{
  if(isActionComplete_) // transactions can only occur once
    return false;

  if(!user_has_movie(*customer_, &item_->movie())) // not enough movies exist
    return false;

  item_->AddToInventory(1);
  customer_->ReturnMovie(&item_->movie());
  customer_->AddTransaction(this);
  isActionComplete_ = true;

  return true;
}

bool Return::user_has_movie(const StoreCustomer& customer, const Movie* movie)
{
  typedef std::list<const Movie*> MovieContainer;
  MovieContainer movies = customer.GetMovies();
  MovieContainer::iterator movie_iter =
    std::find(movies.begin(), movies.end(), movie);

  return (movie_iter != movies.end());
}
