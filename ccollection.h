///////////////////////////////////////////////////////////////////////////////
// CustomerCollection.h
// A collection of CustomerRecords which represents all of a store’s customers
///////////////////////////////////////////////////////////////////////////////
#ifndef CSS343_LAB4_CUSTOMERCOLLECTION_H
#define CSS343_LAB4_CUSTOMERCOLLECTION_H

#include <set>
#include <tr1/unordered_map>
#include <vector>

#include "customer.h"

class CustomerCollection {
public:
  CustomerCollection();
  ~CustomerCollection();

  // The customer's information is added to the program's records and can
  // be retrieved via the customer's id number
  // format: id, name name
  void AddCustomer(std::istream&);

  Customer* GetCustomer(const int) const;

private:
  struct IdHash
  {
    std::size_t operator() (const int) const;
  };

  typedef std::tr1::unordered_map
    <int, Customer*, IdHash>
    CustomerHash;

  std::vector<const Customer*> customer_list_; // holds the raw Customer data
  CustomerHash customer_hash_; // provides constant time lookup

  // Searches for the given customer in the hash list of customers
  // Returns the InventoryItem is found, otherwise returns NULL
  Customer* search_in_hash(const int) const;

  void add_to_hash(Customer*);
};

#endif
