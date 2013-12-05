#include <cstddef>
#include "ccollection.h"

CustomerCollection::CustomerCollection()
{
  // only implemented in c++11
  //customer_hash_.reserve(Customer::kMaxIdNumber);
}

CustomerCollection::~CustomerCollection()
{
  std::vector<const StoreCustomer*>::iterator i;
  for(i = customer_list_.begin(); i != customer_list_.end(); ++i)
    delete *i;
}

void CustomerCollection::AddCustomer(std::istream& input)
{
  StoreCustomer* customer = new StoreCustomer();
  customer->Init(input);

  if(this->search_in_hash(customer->id()) == NULL) { // customer does not exist
    customer_list_.push_back(customer);
    this->add_to_hash(customer);
  } else {
    delete customer; // no longer needed
  }
}

StoreCustomer* CustomerCollection::GetCustomer(const int id) const
{
  return this->search_in_hash(id);
}

std::size_t CustomerCollection::IdHash::operator() (const int id) const
{
  return id;
}

StoreCustomer* CustomerCollection::search_in_hash(const int id) const
{
  CustomerHash::const_iterator result = customer_hash_.find(id);

  if(result != customer_hash_.end())
    //return result->second;
    return *result;

  return NULL;
}

void CustomerCollection::add_to_hash(StoreCustomer* customer)
{
  std::pair<int, StoreCustomer*> hash_element(customer->id(), customer);
  //customer_hash_.insert(hash_element);
  customer_hash_.insert(customer->id(), customer);
}
