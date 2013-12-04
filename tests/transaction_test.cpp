#include <UnitTest++.h>

#include <algorithm>
#include <iostream>
#include <limits>

#include "../inventoryitem.h"
#include "../displaycustomerhistory.h"
#include "../drama.h"
#include "../movie.h"
#include "../borrow.h"
#include "../return.h"
#include "../scustomer.h"
#include "../showmovies.h"
#include "../store.h"
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
    std::stringstream mickey_mouse_data("1234 Mickey Mouse");
    std::stringstream phillippe_data("Phillippe De Broca, King of Hearts, 1967");
    std::stringstream schindler_data("D Steven Spielberg, Schindler's List, 1993");

    schindlers_list = new Drama();
    schindlers_list->Init(schindler_data);

    phillippe = new Drama();
    phillippe->Init(phillippe_data);

    mickey_mouse.Init(mickey_mouse_data);
  }

  ~DefaultData()
  {
    delete schindlers_list;
    delete phillippe;
  }

  StoreCustomer mickey_mouse;
  Movie* schindlers_list;
  Movie* phillippe;
};

SUITE(Borrow_h)
{
  TEST_FIXTURE(DefaultData, Default)
  {
    std::istringstream mickey_data("1234 Mickey Mouse");
    std::istringstream phillippe_data("D Phillippe De Broca, King of Hearts, 1967");
    std::istringstream schindler_data("D Steven Spielberg, Schindler's List, 1993");

    std::istringstream borrow_data("1234 D D Steven Spielberg, Schindler's List,");

    Store store;
    store.AddMovies(schindler_data);
    store.AddMovies(phillippe_data);
    store.AddCustomers(mickey_data);

    Transaction* transaction = new Borrow(store);

    bool transactionComplete = transaction->ExecuteAction(borrow_data);
    CHECK(transactionComplete);
    CHECK_EQUAL(9, transaction->item().GetInventoryCount());
    CHECK_EQUAL("Schindler's List", transaction->item().movie().title());
    CHECK_EQUAL("Mickey Mouse", transaction->customer().name());
  }
}

SUITE(Return_h)
{
  TEST_FIXTURE(DefaultData, Default)
  {
    std::istringstream mickey_data("1234 Mickey Mouse");
    std::istringstream phillippe_data("D Phillippe De Broca, King of Hearts, 1967");
    std::istringstream schindler_data("D Steven Spielberg, Schindler's List, 1993");

    std::istringstream borrow_data("1234 D D Steven Spielberg, Schindler's List,");
    std::istringstream return_data("1234 D D Steven Spielberg, Schindler's List,");

    Store store;
    store.AddMovies(schindler_data);
    store.AddMovies(phillippe_data);
    store.AddCustomers(mickey_data);

    Transaction* borrowAction = new Borrow(store);
    Transaction* returnAction = new Return(store);

    borrowAction->ExecuteAction(borrow_data);
    CHECK_EQUAL(9, borrowAction->item().GetInventoryCount());
    CHECK_EQUAL("Schindler's List", borrowAction->item().movie().title());
    CHECK_EQUAL("Mickey Mouse", borrowAction->customer().name());

    bool transactionComplete = returnAction->ExecuteAction(return_data);

    CHECK(transactionComplete);
    CHECK_EQUAL(10, returnAction->item().GetInventoryCount());
    CHECK_EQUAL("Schindler's List", returnAction->item().movie().title());
    CHECK_EQUAL("Mickey Mouse", returnAction->customer().name());
  }
}

SUITE(ShowMovie_h)
{
  TEST(Default)
  {
     std::istringstream movie_data(
       "D Barry Levinson, Good Morning Vietnam, 1988\n \
       D Gus Van Sant, Good Will Hunting, 2000\n \
       F Woody Allen, Annie Hall, 1977\n \
       D Phillippe De Broca, King of Hearts, 1967\n \
       C George Cukor, The Philadelphia Story, Katherine Hepburn 5 1940\n \
       C Stanley Kubrick, A Clockwork Orange, Malcolm McDowell 2 1971\n \
       F Nora Ephron, You've Got Mail, 1998\n \
     ");

    std::istringstream action_data("1234 D D Steven Spielberg, Schindler's List,");

    Store store;
    store.AddMovies(movie_data);

    Action* action = new ShowMovies(store);

    cout_redirect redirect;
    action->ExecuteAction(action_data);
  }
}

SUITE(DisplayCustomerHistory_h)
{
  TEST(DisplayCustomerHistory_Default)
  {
     std::istringstream movie_data(
      "D Barry Levinson, Good Morning Vietnam, 1988\n \
       D Gus Van Sant, Good Will Hunting, 2000\n \
       F Woody Allen, Annie Hall, 1977\n \
       D Phillippe De Broca, King of Hearts, 1967\n \
       C George Cukor, The Philadelphia Story, Katherine Hepburn 5 1940\n \
       C Stanley Kubrick, A Clockwork Orange, Malcolm McDowell 2 1971\n \
       F Nora Ephron, You've Got Mail, 1998\n \
     ");
    std::stringstream customer_data("1000 Mickey Mouse");
    std::istringstream transaction_data(
      "B 1000 D F You've Got Mail, 1998\n \
       B 1000 D D Barry Levinson, Good Morning Vietnam,\n \
       R 1000 D D Barry Levinson, Good Morning Vietnam,\n \
      ");

    std::istringstream action_data("1000");

    Store store;
    store.AddMovies(movie_data);
    store.AddCustomers(customer_data);
    store.ProcessActions(transaction_data);

    Action* action = new DisplayCustomerHistory(store);
    cout_redirect redirect;
    action->ExecuteAction(action_data);
  }
}
