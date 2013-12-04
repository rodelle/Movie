#include <cstddef>
#include <tr1/unordered_map>

#include "afactory.h"
#include "action.h"
#include "transaction.h"
#include "borrow.h"
#include "return.h"
#include "displaycustomerhistory.h"
#include "showmovies.h"

ActionFactory::ActionFactory()
{
  typedef std::pair<char, ActionFactory::ActionBuilder> Pair;

  action_builder_.insert(Pair('B', ActionFactory::MakeBorrow));
  action_builder_.insert(Pair('R', ActionFactory::MakeReturn));
  action_builder_.insert(Pair('S', ActionFactory::MakeShowMovies));
  action_builder_.insert(Pair('H', ActionFactory::MakeDisplayCustomerHistory));
}

ActionFactory::~ActionFactory()
{}


#include <iostream>
Action* ActionFactory::Create(const char actionType, Store& store) const
{
  BuilderHash::const_iterator builder = action_builder_.find(actionType);
  if(builder != action_builder_.end()) {
    return builder->second(store);
  }

  return NULL; // action type does not exist
}

Action* ActionFactory::MakeBorrow(Store& store)
{ return new Borrow(store); }

Action* ActionFactory::MakeReturn(Store& store)
{ return new Return(store); }

Action* ActionFactory::MakeDisplayCustomerHistory(Store& store)
{ return new DisplayCustomerHistory(store); }

Action* ActionFactory::MakeShowMovies(Store& store)
{ return new ShowMovies(store); }

std::size_t ActionFactory::CharHash::operator() (const char c) const
{
  return c - 'A';
}
