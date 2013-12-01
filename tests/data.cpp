#include <string>
#include <sstream>

#include "data.h"
#include "../scustomer.h"
#include "../movie.h"
#include "../drama.h"
#include "../comedy.h"
#include "../classic.h"

MovieData::MovieData()
{
  schindlers_list = new Drama();
  std::istringstream schindlers_list_data("D Steven Spielberg, Schindler's List, 1993");
  schindlers_list->Init(schindlers_list_data);

  phillippe = new Drama();
  std::istringstream phillippe_data("Phillippe De Broca, King of Hearts, 1967");
  phillippe->Init(phillippe_data);
}

MovieData::~MovieData()
{
  delete schindlers_list;
  delete phillippe;
}

UserData::UserData()
{
  std::istringstream mickey_mouse_data("1234 Mickey Mouse"); 
  mickey_mouse.Init(mickey_mouse_data);
}

UserData::~UserData()
{
}
