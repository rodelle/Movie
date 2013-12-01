///////////////////////////////////////////////////////////////////////////////
// Customer.h
// Represents the attributes of a Customer. Customers are uniquely identified 
// by a 4 digit id number
///////////////////////////////////////////////////////////////////////////////
#ifndef CSS343_LAB4_CUSTOMER_H
#define CSS343_LAB4_CUSTOMER_H

#include <iostream>
#include <string>

class Customer {
public:
  Customer();

  void Init(std::istream&);

  // getters
  int id() const; 
  const std::string& name() const;

protected:
  int id_;
  std::string name_;

  static const int kMinIdNumber;
  static const int kMaxIdNumber;
  void validate_input();
};

#endif
