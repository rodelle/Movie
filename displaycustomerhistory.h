///////////////////////////////////////////////////////////////////////////////
// DisplayCustomerHistory.h
// Allows the store to display the current stock of all movies sorted by their
// categories and then by their respective sorting criteria.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_DISPLAYCUSTOMERHISTORY_H
#define CSS343_LAB4_DISPLAYCUSTOMERHISTORY_H

#include "action.h"

class Store;
class StoreCustomer;

class DisplayCustomerHistory : public Action {
public:
  // Transactions can only exist between a Customer and a MovieItem
  DisplayCustomerHistory(Store&);
  virtual ~DisplayCustomerHistory();

  // Prints out the customer's rental history
  virtual bool ExecuteAction(std::istream&);

private:
  static const int kIdDisplayWidth;
  void print_transaction_history(const StoreCustomer&) const;
  void print_customer_information(const StoreCustomer&) const;
};

#endif
