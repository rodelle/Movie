#include <UnitTest++.h>
#include <cstddef>
#include <iostream>

#include "../afactory.h"
#include "../inventoryitem.h"
#include "../scustomer.h"
#include "../transaction.h"
#include "../borrow.h"
#include "../return.h"
#include "../store.h"
#include "test_helper.h"
#include "data.h"

namespace TFactoryTestHelper
{

}

SUITE(ActionFactory_h)
{
  TEST(Create_nonexistent)
  {
    MovieData md;
    UserData  ud;

    Store store;

    InventoryItem item(*md.phillippe);

    ActionFactory factory;
    Action* transaction = factory.Create('x', store);

    Borrow* borrow = dynamic_cast<Borrow*>(transaction);
    Return* ret = dynamic_cast<Return*>(transaction);

    CHECK(transaction == NULL);
    CHECK(borrow == NULL);
    CHECK(ret == NULL);

    delete transaction;
  }

  TEST(Create_return)
  {
    MovieData md;
    UserData  ud;

    Store store;

    InventoryItem item(*md.phillippe);

    ActionFactory factory;
    Action* transaction = factory.Create('R', store);

    Borrow* borrow = dynamic_cast<Borrow*>(transaction);
    Return* ret = dynamic_cast<Return*>(transaction);

    CHECK(transaction != NULL);
    CHECK(borrow == NULL);
    CHECK(ret != NULL);

    delete transaction;
  }

  TEST(Create_borrow)
  {
    MovieData md;
    UserData  ud;

    InventoryItem item(*md.phillippe);

    Store store;

    ActionFactory factory;
    Action* transaction = factory.Create('B', store);

    Borrow* borrow = dynamic_cast<Borrow*>(transaction);
    Return* ret = dynamic_cast<Return*>(transaction);

    CHECK(transaction != NULL);
    CHECK(borrow != NULL);
    CHECK(ret == NULL);

    delete transaction;
  }
}
