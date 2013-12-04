#include <iomanip>
#include <iostream>

#include "ccollection.h"
#include "displaycustomerhistory.h"
#include "scustomer.h"
#include "store.h"
#include "transaction.h"

DisplayCustomerHistory::DisplayCustomerHistory(Store& store)
  : Action(store)
{}

DisplayCustomerHistory::~DisplayCustomerHistory()
{}

bool DisplayCustomerHistory::ExecuteAction(std::istream& input)
{
  CustomerCollection& customers = store_.customers();

  int customer_id;
  input >> customer_id;

  StoreCustomer& customer = *customers.GetCustomer(customer_id);

  print_customer_information(customer);
  print_transaction_history(customer);

  return true;
}

const int DisplayCustomerHistory::kIdDisplayWidth = 4;

void DisplayCustomerHistory::print_transaction_history(
  const StoreCustomer& customer) const
{
  typedef std::vector<const Transaction*> Transactions;

  Transactions trans_list = customer.GetTransactions();
  Transactions::const_iterator transaction = trans_list.begin();

  // iterate over the list of transactions
  for(; transaction != trans_list.end(); ++transaction) {
    std::cout << **transaction << std::endl;
  }
}

void DisplayCustomerHistory::print_customer_information(
  const StoreCustomer& customer) const
{
  std::cout << " *** Customer ID = "
    << std::setw(kIdDisplayWidth) << customer.id()
    << "  " << customer.name()
    << std::endl;
}
