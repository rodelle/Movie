#include <UnitTest++.h>
#include <fstream>
#include <iostream>
#include <limits>

#include "../store.h"
#include "test_helper.h"

SUITE(Store_h) 
{
  TEST(Customers_default)
  {
    std::istringstream data(
      "3333 Witch Wicked\n \
       6666 Donkey Darrell\n \
       1111 Mouse Mickey\n \
       8000 Wacky Wally\n \
      ");

    Store store;

    store.AddCustomers(data);
    const CustomerCollection& cc = store.customers();

    CHECK_EQUAL("Witch Wicked", cc.GetCustomer(3333)->name());
    CHECK_EQUAL("Donkey Darrell", cc.GetCustomer(6666)->name());
    CHECK_EQUAL("Wacky Wally", cc.GetCustomer(8000)->name());
    CHECK_EQUAL("Mouse Mickey", cc.GetCustomer(1111)->name());
  }

  TEST(Movies_default)
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
  
    typedef std::istringstream iss;
    typedef std::pair<std::string, std::string> SearchStream;
    std::vector<SearchStream> search_data;

    search_data.push_back(SearchStream(
      "You've Got Mail", 
      "D F You've Got Mail, 1998"));
    search_data.push_back(SearchStream(
      "Good Morning Vietnam", 
      "D D Barry Levinson, Good Morning Vietnam,"));
    search_data.push_back(SearchStream(
      "The Philadelphia Story", 
      "D C 5 1940 Katherine Hepburn"));
    search_data.push_back(SearchStream(
      "A Clockwork Orange", 
      "D C 2 1971 Malcolm McDowell"));
    search_data.push_back(SearchStream(
      "Annie Hall", 
      "D F Annie Hall, 1977"));
    search_data.push_back(SearchStream(
      "Good Will Hunting", 
      "D D Gus Van Sant, Good Will Hunting,"));
    search_data.push_back(SearchStream(
      "King of Hearts", 
      "D D Phillippe De Broca, King of Hearts,"));

    Store store;

    store.AddMovies(data);
    const MovieCollection& mc = store.movies();

    std::vector<SearchStream>::iterator i;
    for(i = search_data.begin(); i != search_data.end(); ++i) {
      std::string title = i->first;
      std::istringstream search_stream(i->second);

      std::string return_title = mc.GetMovie(search_stream)->movie().title(); 

      CHECK_EQUAL(title, return_title); 
    }
  }
}
