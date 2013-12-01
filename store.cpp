#include "mcollection.h"
#include "ccollection.h"
#include "store.h"

void Store::AddCustomers(std::istream& input)
{
  do {
    customers_.AddCustomer(input);
  } while(!input.fail());
}

void Store::AddMovies(std::istream& input)
{
  do {
    movies_.AddMovie(input);
  } while(!input.fail());
}

void Store::ProcessTransactions(std::istream& input)
{

}

const MovieCollection& Store::movies()
{ return movies_; }

const CustomerCollection& Store::customers()
{ return customers_; }
