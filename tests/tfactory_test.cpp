#include <UnitTest++.h>
#include <iostream>

#include "../tfactory.h"
#include "../inventoryitem.h"
#include "../scustomer.h"
#include "../transaction.h"
#include "../borrow.h"
#include "../return.h"
#include "test_helper.h"
#include "data.h"

namespace TFactoryTestHelper
{

}

SUITE(TransactionFactory_h) 
{
  TEST(Create_nonexistent) 
  {
    MovieData md;
    UserData  ud;

    InventoryItem item(*md.phillippe);

    TransactionFactory factory;
    Transaction* transaction = factory.Create('x', ud.mickey_mouse, item);
  
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

    InventoryItem item(*md.phillippe);

    TransactionFactory factory;
    Transaction* transaction = factory.Create('R', ud.mickey_mouse, item);

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

    TransactionFactory factory;
    Transaction* transaction = factory.Create('B', ud.mickey_mouse, item);

    Borrow* borrow = dynamic_cast<Borrow*>(transaction);
    Return* ret = dynamic_cast<Return*>(transaction);

    CHECK(transaction != NULL);
    CHECK(borrow != NULL);
    CHECK(ret == NULL);

    delete transaction;
  }
}
