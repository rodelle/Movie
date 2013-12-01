#include <UnitTest++.h>

#include <iostream>
#include <limits>

#include "../inventoryitem.h"
#include "../drama.h"
#include "../movie.h"
#include "../borrow.h"
#include "../return.h"
#include "../scustomer.h"
#include "../transaction.h"

#include "test_helper.h"

static const int kIntMin = std::numeric_limits<int>::min();

namespace TransactionTestHelperFunctions 
{
  bool CustomerContainsMovie(const StoreCustomer& customer, const Movie* movie)
  {
    typedef std::list<const Movie*> MovieContainer;
    MovieContainer movies = customer.GetMovies();
    MovieContainer::iterator movie_iter = 
      std::find(movies.begin(), movies.end(), movie);
    return (movie_iter != movies.end());
  }
}

struct DefaultData
{
  DefaultData()
  {
    schindlers_list = new Drama();
    std::istringstream schindlers_list_data("D Steven Spielberg, Schindler's List, 1993");
    schindlers_list->Init(schindlers_list_data);

    phillippe = new Drama();
    std::istringstream phillippe_data("Phillippe De Broca, King of Hearts, 1967");
    phillippe->Init(phillippe_data);

    std::istringstream mickey_mouse_data("1234 Mickey Mouse"); 
    mickey_mouse.Init(mickey_mouse_data);
  }

  ~DefaultData()
  {
    delete schindlers_list;
    delete phillippe;
  }

  Movie* schindlers_list;
  Movie* phillippe;

  StoreCustomer mickey_mouse;
};

SUITE(Borrow_h) 
{
  TEST_FIXTURE(DefaultData, NotEnoughMovies)
  {
    InventoryItem item(*schindlers_list);

    using namespace TransactionTestHelperFunctions;  

    Transaction* transaction = new Borrow(mickey_mouse, item);

    CHECK_EQUAL(0, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    // should fail because there are 0 items available
    bool transactionComplete = transaction->ExecuteTransaction();

    CHECK(!transactionComplete);
    CHECK_EQUAL(0, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    // continues to fail
    transactionComplete = transaction->ExecuteTransaction();

    CHECK(!transactionComplete);
    CHECK_EQUAL(0, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    delete transaction;
  } 

  TEST_FIXTURE(DefaultData, Default)
  {
    InventoryItem item(*schindlers_list);
    item.AddToInventory(10); 

    using namespace TransactionTestHelperFunctions;  

    Transaction* transaction = new Borrow(mickey_mouse, item);

    CHECK_EQUAL(10, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    bool transactionComplete = transaction->ExecuteTransaction();

    CHECK(transactionComplete);
    CHECK_EQUAL(9, item.GetInventoryCount());
    CHECK(CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    delete transaction;
  }

  TEST_FIXTURE(DefaultData, MultipleExecutions)
  {
    InventoryItem item(*schindlers_list);
    item.AddToInventory(10); 

    using namespace TransactionTestHelperFunctions;  

    Transaction* transaction = new Borrow(mickey_mouse, item);

    // Multiple transactions should have no effect after the first
    bool transactionComplete = transaction->ExecuteTransaction(); // first transaction

    CHECK(transactionComplete);
    CHECK_EQUAL(9, item.GetInventoryCount());
    CHECK(CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    transactionComplete = transaction->ExecuteTransaction(); // second transaction
    
    CHECK(!transactionComplete);
    CHECK_EQUAL(9, item.GetInventoryCount());
    CHECK(CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    transactionComplete = transaction->ExecuteTransaction(); // third transaction
    
    CHECK(!transactionComplete);
    CHECK_EQUAL(9, item.GetInventoryCount());
    CHECK(CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    delete transaction;
  }
}

SUITE(Return_h) 
{
  TEST_FIXTURE(DefaultData, Default)
  {
    InventoryItem item(*schindlers_list);
    item.AddToInventory(10); 

    using namespace TransactionTestHelperFunctions;  

    Transaction* transaction = new Return(mickey_mouse, item);
    mickey_mouse.CheckoutMovie(schindlers_list);

    CHECK_EQUAL(10, item.GetInventoryCount());
    CHECK(CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    bool transactionComplete = transaction->ExecuteTransaction();

    CHECK(transactionComplete);
    CHECK_EQUAL(11, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    delete transaction;
  }

  TEST_FIXTURE(DefaultData, UserDoesNotHaveMovie)
  {
    InventoryItem item(*schindlers_list);

    using namespace TransactionTestHelperFunctions;  

    Transaction* transaction = new Return(mickey_mouse, item);

    CHECK_EQUAL(0, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));

    // should fail because user never rented the movie 
    bool transactionComplete = transaction->ExecuteTransaction();

    CHECK(!transactionComplete);
    CHECK_EQUAL(0, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));

    // continues to fail
    transactionComplete = transaction->ExecuteTransaction();

    CHECK(!transactionComplete);
    CHECK_EQUAL(0, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));

    delete transaction;
  } 

  TEST_FIXTURE(DefaultData, MultipleExecutions)
  {
    InventoryItem item(*schindlers_list);
    item.AddToInventory(10); 

    using namespace TransactionTestHelperFunctions;  

    mickey_mouse.CheckoutMovie(schindlers_list);
    Transaction* transaction = new Return(mickey_mouse, item);

    CHECK_EQUAL(10, item.GetInventoryCount());
    CHECK(CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    bool transactionComplete = transaction->ExecuteTransaction(); // first transaction

    CHECK(transactionComplete);
    CHECK_EQUAL(11, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    // Multiple transactions should have no effect after the first
    transactionComplete = transaction->ExecuteTransaction(); // second transaction
    
    CHECK(!transactionComplete);
    CHECK_EQUAL(11, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    transactionComplete = transaction->ExecuteTransaction(); // third transaction
    
    CHECK(!transactionComplete);
    CHECK_EQUAL(11, item.GetInventoryCount());
    CHECK(!CustomerContainsMovie(mickey_mouse, schindlers_list));
    CHECK(!CustomerContainsMovie(mickey_mouse, phillippe));

    delete transaction;
  }
}
