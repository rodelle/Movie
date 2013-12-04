///////////////////////////////////////////////////////////////////////////////
// Customer.h
// Represents the attributes of a Customer. Customers are uniquely identified
// by a 4 digit id number
//
// author: Rodelle Ladia Jr.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_CUSTOMER_H
#define CSS343_LAB4_CUSTOMER_H

#include <iostream>
#include <string>

class Customer {
public:
  Customer();

  // Initialize the object using information from the stream
  //
  // @param stream in the following format
  // format: "id    firstname lastname"
  //          int   string    string
  void Init(std::istream&);

  // getters
  int id() const;
  const std::string& name() const;

protected:
  static const int kMinIdNumber;
  static const int kMaxIdNumber;

  int id_;
  std::string name_;

  // Checks to make sure the id is within the valid range
  // If it isn't, sets it to default kMinIdNumber
  void validate_input();
};

#endif
