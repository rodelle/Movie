#ifndef CSS343_LAB4_TESTDATA_H
#define CSS343_LAB4_TESTDATA_H

class Movie;

#include "../scustomer.h"

struct MovieData 
{
  MovieData();
  ~MovieData();
  
  Movie* schindlers_list;
  Movie* phillippe;
};

struct UserData
{
  UserData();
  ~UserData();

  StoreCustomer mickey_mouse;
};

#endif
