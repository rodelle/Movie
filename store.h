///////////////////////////////////////////////////////////////////////////////
// Store.h
// The store class receives user input and calls the underlying logic to
// perform the command
///////////////////////////////////////////////////////////////////////////////
#ifndef CSS343_LAB4_STORE_H
#define CSS343_LAB4_STORE_H

#include <istream>

#include "mcollection.h"
#include "ccollection.h"
#include "afactory.h"

class StoreCustomer;

class Store {
public:
  void AddCustomers(std::istream&);
  void AddMovies(std::istream&);
  void ProcessTransactions(std::istream&);

  MovieCollection& movies();
  CustomerCollection& customers();

private:
  // collection of MovieItems
  MovieCollection movies_;

  // collection of CustomerRecords
  CustomerCollection customers_;

  ActionFactory factory_;
};

#endif
