///////////////////////////////////////////////////////////////////////////////
// DisplayCustomerHistory.h
// Allows the store to display the current stock of all movies sorted by their
// categories and then by their respective sorting criteria.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_DISPLAYCUSTOMERHISTORY_H
#define CSS343_LAB4_DISPLAYCUSTOMERHISTORY_H

#include "saction.h"

class StoreCustomer;
class MovieCollection;
class Transaction;

class DisplayCustomerHistory : public StoreAction {
public:
  // Transactions can only exist between a Customer and a MovieItem
  DisplayCustomerHistory();
  virtual ~DisplayCustomerHistory();

  // Prints out the customer's rental history
  virtual void ExecuteAction(const StoreCustomer&);

  // Does nothing
  virtual void ExecuteAction(const MovieCollection&);

private:
  static const int kIdDisplayWidth;
  void print_transaction_information(const Transaction&) const;
  void print_customer_information(const StoreCustomer&) const;
};

#endif
