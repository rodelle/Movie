#include <iostream>
#include <fstream>

#include "store.h"

int main()
{
  std::ifstream movie_data("data4movies.txt");
  std::ifstream customer_data("data4customers.txt");
  std::ifstream action_data("data4commands.txt");

  if(!movie_data) {
    std::cout << "data4movies.txt could not be opened\n";
    return 1;
  }

  if(!customer_data) {
    std::cout << "data4customers.txt could not be opened\n";
    return 1;
  }

  if(!action_data) {
    std::cout << "data4commands.txt could not be opened\n";
    return 1;
  }

  Store store;

  store.AddMovies(movie_data);
  store.AddCustomers(customer_data);
  store.ProcessActions(action_data);

  std::cout << "Main complete\n";
  return 0;
}
