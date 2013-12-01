#include <cstddef>
#include "ccollection.h"

CustomerCollection::CustomerCollection()
{
  // only implemented in c++11
  //customer_hash_.reserve(Customer::kMaxIdNumber - Customer::kMinIdNumber);
}

CustomerCollection::~CustomerCollection()
{
  std::vector<const Customer*>::iterator i;
  for(i = customer_list_.begin(); i != customer_list_.end(); ++i)
    delete *i;
}

void CustomerCollection::AddCustomer(std::istream& input)
{
  Customer* customer = new Customer();
  customer->Init(input);

  if(this->search_in_hash(customer->id()) == NULL) { // customer does not exist 
    customer_list_.push_back(customer);
    this->add_to_hash(customer);
  }
}

Customer* CustomerCollection::GetCustomer(const int id) const
{
  return this->search_in_hash(id);
}

std::size_t CustomerCollection::IdHash::operator() (const int id) const
{
  return id - Customer::kMinIdNumber;
}

Customer* CustomerCollection::search_in_hash(const int id) const
{
  CustomerHash::const_iterator result = customer_hash_.find(id); 

  if(result != customer_hash_.end())
    return result->second;

  return NULL;
}

void CustomerCollection::add_to_hash(Customer* customer)
{
  std::pair<int, Customer*> hash_element(customer->id(), customer);
  customer_hash_.insert(hash_element);
}

