#include <algorithm>
#include <iostream>

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
  if(!user_has_movie(*customer_, &item_->movie())) { // not enough movies exist
    std::cout << "** Error in Return: \"" << customer_->name()
      << "\" has not previously borrowed \"" << item_->movie().title() << "\"\n";
    return false;
  }

  item_->AddToRemaining(1, mediatype_);
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
