#include "movie.h"
#include "scustomer.h"
#include "transaction.h"

StoreCustomer::~StoreCustomer()
{
  std::vector<const Transaction*>::iterator i;
  for(i = transactions_.begin(); i != transactions_.end(); ++i) {
    delete *i;
  }
}

void StoreCustomer::AddTransaction(const Transaction* transaction)
{
  transactions_.push_back(transaction);
}

void StoreCustomer::CheckoutMovie(const Movie* movie)
{
  movies_.push_back(movie);
}

void StoreCustomer::ReturnMovie(const Movie* movie)
{
  movies_.remove(movie);
}

void StoreCustomer::Print()
{

}

const std::vector<const Transaction*>& StoreCustomer::GetTransactions() const
{
  return transactions_;
}

const std::list<const Movie*>& StoreCustomer::GetMovies() const
{
  return movies_;
}

