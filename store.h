///////////////////////////////////////////////////////////////////////////////
// Store.h
// The store class receives user input and calls the underlying logic to
// perform the command
//
// author: Rodelle Ladia Jr.
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
  // Processes the stream and adds the information to the Store's records.
  void AddCustomers(std::istream&);
  void AddMovies(std::istream&);

  // Performs the actions outlined by the information in the stream
  void ProcessActions(std::istream&);

  // getters
  MovieCollection& movies();
  CustomerCollection& customers();

private:
  // collection of MovieItems
  MovieCollection movies_;

  // collection of CustomerRecords
  CustomerCollection customers_;

  // Factory used to create Actions
  ActionFactory factory_;
};

#endif
