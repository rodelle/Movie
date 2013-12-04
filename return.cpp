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

bool Return::commit_transaction()
{
  if(!user_has_movie(*customer_, &item_->movie())) // not enough movies exist
    return false;

  item_->AddToRemaining(1);
  customer_->ReturnMovie(&item_->movie());
  customer_->AddTransaction(this);

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
