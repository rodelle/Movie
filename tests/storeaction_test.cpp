#include <UnitTest++.h>

#include <algorithm>
#include <iostream>
#include <limits>

#include "../mcollection.h"
#include "../saction.h"
#include "../showmovies.h"
#include "../scustomer.h"

#include "test_helper.h"

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
