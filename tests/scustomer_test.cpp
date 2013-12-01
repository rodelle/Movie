#include <UnitTest++.h>
#include <algorithm>
#include <iostream>
#include <limits>

#include "../scustomer.h"
#include "../movie.h"
#include "../drama.h"
#include "test_helper.h"

static const int kIntMin = std::numeric_limits<int>::min();

namespace StoreCustomerTestFunctions 
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

SUITE(StoreCustomer_h) 
{
  TEST(AddMovie_default)
  {
    std::istringstream schindlers_list_data("D Steven Spielberg, Schindler's List, 1993");
    Movie* schindlers_list = new Drama();
    schindlers_list->Init(schindlers_list_data);

    std::istringstream phillippe_data("Phillippe De Broca, King of Hearts, 1967");
    Movie* phillippe = new Drama();
    phillippe->Init(phillippe_data);

    std::istringstream customer_data("1234 Mickey Mouse"); 
    StoreCustomer customer;
    customer.Init(customer_data);

    customer.CheckoutMovie(schindlers_list);
    customer.CheckoutMovie(phillippe);

    using namespace StoreCustomerTestFunctions;  
    CHECK(CustomerContainsMovie(customer, schindlers_list));
    CHECK(CustomerContainsMovie(customer, phillippe));

    customer.ReturnMovie(schindlers_list);
    CHECK(!CustomerContainsMovie(customer, schindlers_list));
    CHECK(CustomerContainsMovie(customer, phillippe));

    customer.ReturnMovie(phillippe);
    CHECK(!CustomerContainsMovie(customer, schindlers_list));
    CHECK(!CustomerContainsMovie(customer, phillippe));
  }

  TEST(Construction_default)
  {
    std::istringstream default_data("1234 Mickey Mouse"); 
    StoreCustomer customer;
    customer.Init(default_data);

    CHECK_EQUAL(1234, customer.id());
    CHECK_EQUAL("Mickey Mouse", customer.name());
  }

  TEST(InvalidId)
  {
    std::istringstream id_too_small("0 Mickey Mouse"); 
    StoreCustomer customer;
    customer.Init(id_too_small);

    CHECK_EQUAL(kIntMin, customer.id());
    CHECK_EQUAL("Mickey Mouse", customer.name());

    std::istringstream id_too_large("12345 Mickey Mouse"); 
    customer.Init(id_too_large);

    CHECK_EQUAL(kIntMin, customer.id());
    CHECK_EQUAL("Mickey Mouse", customer.name());  
  }
}
