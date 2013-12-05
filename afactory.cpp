#include <tr1/unordered_map>

#include <cstddef>
#include <iostream>

#include "action.h"
#include "afactory.h"
#include "borrow.h"
#include "displaycustomerhistory.h"
#include "return.h"
#include "showmovies.h"
#include "transaction.h"

ActionFactory::ActionFactory()
{
  typedef std::pair<char, ActionFactory::ActionBuilder> Pair;

  // Built from the known concrete Action classes
  action_builder_.insert(Pair('B', ActionFactory::MakeBorrow));
  action_builder_.insert(Pair('R', ActionFactory::MakeReturn));
  action_builder_.insert(Pair('S', ActionFactory::MakeShowMovies));
  action_builder_.insert(Pair('H', ActionFactory::MakeDisplayCustomerHistory));
}

ActionFactory::~ActionFactory()
{}

Action* ActionFactory::Create(const char actionType, Store& store) const
{
  // search the map looking for the given action type
  BuilderHash::const_iterator builder = action_builder_.find(actionType);
  if(builder != action_builder_.end()) { // action exists
    return builder->second(store);
  } // else { // action type does not exist

  std::cout << "** Error in ActionFactory.\
    The specified action does not exist\n";
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

// mapping from ascii values to index
// eg. 'A' => 0, 'B' =>1, ... 'Z' => 25
std::size_t ActionFactory::CharHash::operator() (const char c) const
{
  return c - 'A';
}
