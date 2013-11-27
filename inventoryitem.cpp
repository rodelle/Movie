//////////////////////////////////////////////////////////////////////////////
// inventoryitem.h
// Responsible for keeping track of current number of movies that a store 
// owns, and the number currently checked out. 
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tr1/unordered_map>
#include "movie.h"
#include "comedy.h"

struct CharHash {
  std::size_t operator() (char c) const
  {
    return 1;
  }
};

class InventoryItem {
public:
  InventoryItem() 
  {
    movie_ = new Comedy("A");
    std::cout << *movie_;
  }
  void Remove(Movie&, char);
  void Add(Movie&, char);
private:
  typedef std::tr1::unordered_map<char, int, CharHash> InventoryHash;
  Movie* movie_;
  InventoryHash inventory_;
};

int main()
{
  InventoryItem a;
  return 0;
}
