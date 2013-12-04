#include <cstddef>

#include "action.h"
#include "afactory.h"
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
  while(true) {
    char actionType;
    input >> actionType;

    if(input.fail())
      break;

    input.get(); // get rid of extra space

    Action* action = factory_.Create(actionType, *this);

    if(action != NULL) // valid action type
      if(action->ExecuteAction(input) == false)
        delete action; // action was not completed
  }
}

MovieCollection& Store::movies()
{ return movies_; }

CustomerCollection& Store::customers()
{ return customers_; }
