///////////////////////////////////////////////////////////////////////////////
// StoreAction.h
// StoreAction is a base class from which the different concrete types of 
// action inherit. Each action represents the store displaying information 
// about its current state
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_STOREACTION_H
#define CSS343_LAB4_STOREACTION_H

class StoreCustomer;
class MovieCollection;

class StoreAction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  StoreAction();
  virtual ~StoreAction();

  // Performs the necessary operations to execute the action 
  virtual void ExecuteAction(const StoreCustomer&) = 0;
  virtual void ExecuteAction(const MovieCollection&) = 0;
};

#endif
