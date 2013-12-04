///////////////////////////////////////////////////////////////////////////////
// StoreCustomer.h
// Extends customer and adds a list of transactions and checked out movies
///////////////////////////////////////////////////////////////////////////////
#ifndef CSS343_LAB4_STORECUSTOMER_H
#define CSS343_LAB4_STORECUSTOMER_H

#include "customer.h"
#include <vector>
#include <list>

class Transaction;
class Movie;

class StoreCustomer : public Customer {
public:
  ~StoreCustomer();

  // Appends the transaction to the customer's list of transactions
  // This class takes ownership of the memory allocated for the Transaction
  // and is reponsible for cleaning it up
  void AddTransaction(const Transaction*);

  // modifes the list of checked out movies
  void CheckoutMovie(const Movie*);
  void ReturnMovie(const Movie*);

  // prints all transaction history associated with the customer
  void Print();

  const std::vector<const Transaction*>& GetTransactions() const;
  const std::list<const Movie*>& GetMovies() const;
private:
  // list of of the transactions involving this customer
  std::vector<const Transaction*> transactions_;

  // list of items that the customer currently has checked out.
  std::list<const Movie*> movies_;
};

#endif
