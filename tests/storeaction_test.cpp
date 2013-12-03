#include <UnitTest++.h>

#include <algorithm>
#include <iostream>
#include <limits>

#include "../borrow.h"
#include "../classic.h"
#include "../comedy.h"
#include "../displaycustomerhistory.h"
#include "../drama.h"
#include "../mcollection.h"
#include "../movie.h"
#include "../return.h"
#include "../saction.h"
#include "../showmovies.h"
#include "../scustomer.h"

#include "test_helper.h"

SUITE(DisplayCustomerHistory_h)
{
  TEST(Default)
  {
    std::istringstream data("1234 Mickey Mouse");
    StoreCustomer customer;
    customer.Init(data);

    Movie* schindlers_list = new Drama();
    std::istringstream schindlers_list_data("D Steven Spielberg, Schindler's List, 1993");
    schindlers_list->Init(schindlers_list_data);
    InventoryItem item1(*schindlers_list);
    item1.AddToInventory(10);
    Transaction* transaction1 = new Borrow(customer, item1);
    transaction1->ExecuteTransaction();

    Movie* phillippe = new Drama();
    std::istringstream phillippe_data("Phillippe De Broca, King of Hearts, 1967");
    phillippe->Init(phillippe_data);
    InventoryItem item2(*phillippe);
    item2.AddToInventory(10);
    Transaction* transaction2 = new Borrow(customer, item2);
    transaction2->ExecuteTransaction();

    StoreAction* action = new DisplayCustomerHistory();
    action->ExecuteAction(customer);

    delete schindlers_list;
    delete phillippe;
    delete transaction1;
    delete transaction2;
    delete action;
  }
}
/*
SUITE(ShowMovies_h)
{
  TEST(Default)
  {
    std::istringstream data(
     "D Barry Levinson, Good Morning Vietnam, 1988\n \
      D Gus Van Sant, Good Will Hunting, 2000\n \
      F Woody Allen, Annie Hall, 1977\n \
      D Phillippe De Broca, King of Hearts, 1967\n \
      C George Cukor, The Philadelphia Story, Katherine Hepburn 5 1940\n \
      C Stanley Kubrick, A Clockwork Orange, Malcolm McDowell 2 1971\n \
      F Nora Ephron, You've Got Mail, 1998\n \
    ");

    MovieCollection movies;
    for(int i = 0; i < 7; ++i)
      movies.AddMovie(data);

    StoreAction* action = new ShowMovies();
    action->ExecuteAction(movies);

    delete action;
  }
}
*/
