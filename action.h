///////////////////////////////////////////////////////////////////////////////
// Action.h
// Action is a base class from which the different concrete types of
// derived transactions inherit. Actions contain the logic to perform
// business functions such as, checking out movies to customers or displaying
// all of the movies in stock
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_ACTION_H
#define CSS343_LAB4_ACTION_H

#include <string>

class Store;

class Action {
friend std::ostream& operator<<(std::ostream&, const Action&);
public:
  // Actions need access to the store's data
  Action(Store&);
  virtual ~Action();

  // Performs the necessary operations to execute the transaction
  virtual bool ExecuteAction(std::istream&) = 0;

  // getters
  virtual const std::string& name() const;

protected:
  Store& store_; // the store whose data will be modified or viewed
  bool isActionComplete_; // represents whether the action was claimed
  std::string name_;
};

#endif
