#include <UnitTest++.h>
#include <iostream>
#include <limits>

#include "../customer.h"
#include "test_helper.h"

static const int kIntMin = std::numeric_limits<int>::min();

SUITE(Customer_h)
{
  TEST(Construction_default)
  {
    std::istringstream default_data("1234 Mickey Mouse");
    Customer customer;
    customer.Init(default_data);

    CHECK_EQUAL(1234, customer.id());
    CHECK_EQUAL("Mickey Mouse", customer.name());
  }

  TEST(InvalidId)
  {
    std::istringstream id_too_small("0 Mickey Mouse");
    Customer customer;
    customer.Init(id_too_small);

    CHECK_EQUAL(kIntMin, customer.id());
    CHECK_EQUAL("Mickey Mouse", customer.name());

    std::istringstream id_too_large("12345 Mickey Mouse");
    customer.Init(id_too_large);

    CHECK_EQUAL(kIntMin, customer.id());
    CHECK_EQUAL("Mickey Mouse", customer.name());  }
}
