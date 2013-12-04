//////////////////////////////////////////////////////////////////////////////
// inventoryitem.h
// Responsible for keeping track of current number of movies that a store
// owns.
//
// author: Rodelle Ladia Jr.
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
  void RemoveFromInventory(const int = 1, const char = kDefaultMediaType);

  // Adds additional items to the available inventory for this item. The
  // remaining movies will be increased by the given amount.
  // @param mediaType - the type of media being added to the inventory
  // @param amount - the number of items to add to the inventory
  void AddToTotal(const int = 1, const char = kDefaultMediaType);
  void AddToRemaining(const int = 1, const char = kDefaultMediaType);

  // Returns how many movies of the given type are remaining
  // @param mediaType - the media type inventory count to return
  int GetRemaining(const char = kDefaultMediaType) const;

  // Returns the total number of movies owned by the store
  // @param mediaType - the media type inventory count to return
  int GetTotal(const char = kDefaultMediaType) const;

  // Returns whether there are enough items remaining to fulfill the request
  // order size
  // @param mediaType - the media type to check for
  // @param orderSize - the requested number of items to provide
  bool Contains(const int = 1, const char = kDefaultMediaType) const;

  // Returns the movie
  const Movie& movie() const;

  // default media type used for operations
  static const char kDefaultMediaType;
  static const char* kDefaultMediaName;

private:
  struct Inventory {
    int total;
    int remaining;
  };

  struct CharHash { // Returns the hash value for a char
    std::size_t operator() (const char) const;
  };
  typedef std::tr1::unordered_map<char, Inventory, CharHash> MediaInventory;

  const Movie& movie_;
  MediaInventory inventory_; // holds the available number of movies of a type
};

#endif
