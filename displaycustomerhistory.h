///////////////////////////////////////////////////////////////////////////////
// DisplayCustomerHistory.h
// Contains logic needed to access a customer's rental history and print that
// information to the screen
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_DISPLAYCUSTOMERHISTORY_H
#define CSS343_LAB4_DISPLAYCUSTOMERHISTORY_H

#include "action.h"

class Store;
class StoreCustomer;

class DisplayCustomerHistory : public Action {
public:
  DisplayCustomerHistory(Store&);
  virtual ~DisplayCustomerHistory();

  // Prints out the customer's rental history
  virtual bool ExecuteAction(std::istream&);

private:
  static const int kIdDisplayWidth;
  // prints the list of transactions by the customer with one
  // transaction per line
  void print_transaction_history(const StoreCustomer&) const;

  // Prints out the customers id number and name
  void print_customer_information(const StoreCustomer&) const;
};

#endif
