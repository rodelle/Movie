#include "customer.h"

#include <boost/algorithm/string.hpp>

#include <limits>
#include <string>

const int Customer::kMinIdNumber = 1;
const int Customer::kMaxIdNumber = 9999;

Customer::Customer()
  : id_(kMinIdNumber)
{}

// format: id_num, name name
void Customer::Init(std::istream& input)
{
  input >> id_;
  std::getline(input, name_);

  boost::algorithm::trim(name_);

  validate_input();
}

void Customer::validate_input()
{
  if(id_ < kMinIdNumber || id_ > kMaxIdNumber)
    id_ = std::numeric_limits<int>::min();
}

int Customer::id() const
{
  return id_;
}

const std::string& Customer::name() const
{
  return name_;
}
