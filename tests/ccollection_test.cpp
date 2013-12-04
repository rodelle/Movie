#include <UnitTest++.h>
#include <iostream>

#include "../ccollection.h"
#include "../customer.h"
#include "test_helper.h"

struct CustomerData
{
  CustomerData()
  {
    SetData(
      data_mickey_mouse, "1234 Mickey Mouse",
      search_mickey_mouse, 1234);
  }

  std::istringstream data_mickey_mouse;
  int search_mickey_mouse;

private:
  void SetData(
    std::istringstream& customer_data,
    const std::string& data_string,
    int& search_data,
    const int search_value)
  {
    customer_data.str(data_string);
    search_data = search_value;
  }

};

SUITE(CCollection_h)
{
  TEST_FIXTURE(CustomerData, Default)
  {
    CustomerCollection customers;
    customers.AddCustomer(data_mickey_mouse);

    Customer* customer = customers.GetCustomer(search_mickey_mouse);

    CHECK_EQUAL(1234, customer->id());
    CHECK_EQUAL("Mickey Mouse", customer->name());
  }
}
