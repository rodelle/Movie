#include <algorithm>
#include "return.h"
#include "scustomer.h"
#include "inventoryitem.h"

Return::Return(StoreCustomer& customer, InventoryItem& item)
  : Transaction(customer, item) 
{}

Return::~Return()
{}

bool Return::ExecuteTransaction()
{
  if(isTransactionComplete_) // transactions can only occur once
    return false; 
  
  if(!user_has_movie(customer_, &(item_.movie()))) // not enough movies exist
    return false;

  item_.AddToInventory(1);
  customer_.ReturnMovie(&item_.movie()); 
  isTransactionComplete_ = true;

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
