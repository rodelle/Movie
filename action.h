///////////////////////////////////////////////////////////////////////////////
// Action.h
// Action is a base class from which the different concrete types of
// derived transactions inherit. Each transaction represents an association
// between a customer and an inventoryitem
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_ACTION_H
#define CSS343_LAB4_ACTION_H

#include <string>

class Store;

class Action {
friend std::ostream& operator<<(std::ostream&, const Action&);
public:
  // Actions can only exist between a Customer and a MovieItem
  Action(Store&);
  virtual ~Action();

  // Performs the necessary operations to execute the transaction
  virtual bool ExecuteAction(std::istream&) = 0;

  // getters
  virtual const std::string& name() const;

protected:
  Store& store_;

  // Actions can only be completed once
  bool isActionComplete_;
  std::string name_;
};

#endif
