#include <iomanip>
#include <iostream>

#include "displaycustomerhistory.h"
#include "scustomer.h"
#include "mcollection.h"
#include "transaction.h"

DisplayCustomerHistory::DisplayCustomerHistory()
{}

DisplayCustomerHistory::~DisplayCustomerHistory()
{}

void DisplayCustomerHistory::ExecuteAction(const MovieCollection& movie_collection)
{}

void DisplayCustomerHistory::ExecuteAction(const StoreCustomer& customer)
{
  print_customer_information(customer);

  typedef std::vector<const Transaction*> Transactions;

  Transactions trans_list = customer.GetTransactions();
  Transactions::const_iterator transaction = trans_list.begin();

  // iterate over the list of transactions
  for(; transaction != trans_list.end(); ++transaction) {
    print_transaction_information(**transaction);
  }
}

const int DisplayCustomerHistory::kIdDisplayWidth = 4;

void DisplayCustomerHistory::print_transaction_information(
  const Transaction& transaction) const
{
  std::cout << transaction << std::endl;
}

void DisplayCustomerHistory::print_customer_information(
  const StoreCustomer& customer) const
{
  std::cout << " *** Customer ID = "
    << std::setw(kIdDisplayWidth) << customer.id()
    << "  " << customer.name()
    << std::endl;
}
