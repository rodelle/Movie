#include <cstddef>

#include "ccollection.h"

CustomerCollection::CustomerCollection()
{
  // only implemented in c++11
  //customer_hash_.reserve(Customer::kMaxIdNumber);
}

CustomerCollection::~CustomerCollection()
{
  // delete the customer data
  std::vector<const StoreCustomer*>::iterator i;
  for(i = customer_list_.begin(); i != customer_list_.end(); ++i)
    delete *i;
}

void CustomerCollection::AddCustomer(std::istream& input)
{
  StoreCustomer* customer = new StoreCustomer();
  customer->Init(input); // allow the customer to initialize itself

  if(search_in_hash(customer->id()) == NULL) { // customer does not exist
    // add to containers
    customer_list_.push_back(customer); // holds raw data
    add_to_hash(customer); // fast lookup
  } else {
    std::cout << "** Error in Customer Collection. \
      Customer already exists and was not added. \n";
    delete customer; // no longer needed
  }
}

StoreCustomer* CustomerCollection::GetCustomer(const int id) const
{
  // returns NULL if the search was unsuccessful
  return search_in_hash(id);
}

// simple map from id => index
std::size_t CustomerCollection::IdHash::operator() (const int id) const
{
  return id;
}

// fast lookup in the has
StoreCustomer* CustomerCollection::search_in_hash(const int id) const
{
  CustomerHash::const_iterator result = customer_hash_.find(id);

  if(result != customer_hash_.end()) // customer was not found in the hash
    //return result->second; // tr1/unordered_map implementation
    return *result;

  return NULL;
}

void CustomerCollection::add_to_hash(StoreCustomer* customer)
{
  // tr1/unordered_map implementation
  //std::pair<int, StoreCustomer*> hash_element(customer->id(), customer);
  //customer_hash_.insert(hash_element);
  customer_hash_.insert(customer->id(), customer);
}
