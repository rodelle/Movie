//////////////////////////////////////////////////////////////////////////////
// inventoryitem.h
// Responsible for keeping track of current number of movies that a store 
// owns.
//////////////////////////////////////////////////////////////////////////////
#ifndef CSS343_LAB4_INVENTORYITEM_H
#define CSS343_LAB4_INVENTORYITEM_H

#include <tr1/unordered_map>

#include "movie.h"

class InventoryItem {
public:
  // default ctor
  // @param movie the movie referenced by the media types 
  InventoryItem(const Movie&);

  // Removes the media item from the inventory. The remaining movies will be
  // reduced by the given amount.
  // @param mediaType - media type to be removed
  // @param amount - the number of items to remove from the inventory 
  void RemoveFromInventory(char = kDefaultMediaType, int = 1); // defaults to DVD

  // Adds additional items to the available inventory for this item. The
  // remaining movies will be increased by the given amount.
  // @param mediaType - the type of media being added to the inventory 
  // @param amount - the number of items to add to the inventory   
  void AddToInventory(char = kDefaultMediaType, int = 1); // defaults to DVD

  // Returns how many movies of the given type are remaining
  // @param mediaType - the media type inventory count to return
  int GetInventoryCount(char = kDefaultMediaType);

  // Returns whether there are enough items remaining to fulfill the request
  // order size
  // @param mediaType - the media type to check for
  // @param orderSize - the requested number of items to provide 
  bool Contains(char = kDefaultMediaType, int = 1);


  // Returns the movie
  const Movie& movie() const;

private:
  // Returns the hash value for a char
  struct CharHash
  {
    std::size_t operator() (char) const;
  };
  typedef std::tr1::unordered_map<char, int, CharHash> MediaInventory;

  // default media type used for operations 
  static const char kDefaultMediaType; 

  const Movie& movie_; // the movie 
  MediaInventory inventory_; // holds the available number of movies of a type
};

#endif
