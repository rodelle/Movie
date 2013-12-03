#include <cstddef>
#include <tr1/unordered_map>

#include "afactory.h"
#include "action.h"
#include "transaction.h"
#include "borrow.h"
#include "return.h"

ActionFactory::ActionFactory()
{
  typedef std::pair<char, ActionFactory::ActionBuilder> Pair;

  action_builder_.insert(Pair('B', ActionFactory::MakeBorrow));
  action_builder_.insert(Pair('R', ActionFactory::MakeReturn));
}

ActionFactory::~ActionFactory()
{}

Action* ActionFactory::Create(const char actionType, Store& store) const
{
  if(action_builder_.count(actionType) == 1) {
    ActionBuilder builder =
      action_builder_.find(actionType)->second;
    return builder(store);
  }

  return NULL; // action type does not exist
}

Action* ActionFactory::MakeBorrow(Store& store)
{ return new Borrow(store); }

Action* ActionFactory::MakeReturn(Store& store)
{ return new Return(store); }

std::size_t ActionFactory::CharHash::operator() (const char c) const
{
  return c - 'A';
}
