#include "scustomer.h"
#include "inventoryitem.h"
#include "transaction.h"

Action::Action(Store& store)
  : store_(store), isActionComplete_(false), name_("")
{}

Action::~Action()
{}


std::ostream& operator<<(std::ostream& out, const Action& transaction)
{
  out << transaction.name_
  return out;
}

const std::string& Action::name() const
{ return name_; }
