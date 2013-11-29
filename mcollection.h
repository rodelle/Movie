///////////////////////////////////////////////////////////////////////////////
// MovieCollection.h
// MovieCollection is a collection of movies owned by a store. Movies can be 
// added and retrieved from the collection. 
///////////////////////////////////////////////////////////////////////////////
#ifndef CSS343_LAB4_MOVIECOLLECTION_H
#define CSS343_LAB4_MOVIECOLLECTION_H

#include <boost/functional/hash.hpp>
#include <set>
#include <tr1/unordered_map>
#include <vector>

#include "inventoryitem.h"
#include "mfactory.h"
#include "movie.h"

class MovieCollection {
public:
  MovieCollection();
  ~MovieCollection();

  // 10 new copies of the movie are added to the store’s inventory.
  void AddMovie(std::istream&);

  // Retrieves previously added movies from the collection. If the identifier can be mapped 
  // to a unique movie, the complexity of this call is O(1). If the identifier cannot be mapped
  // to a unique movie, the complexity of this call is O(logN).
  InventoryItem GetMovie(std::istream&);

private:
  struct MovieCompare
  { 
    bool operator() (const InventoryItem*, const InventoryItem*) const;
  };

  struct MovieHash
  { 
    std::size_t operator() (const std::string&) const;
    static boost::hash<std::string> string_hash;
  };

  typedef std::tr1::unordered_map<std::string, const InventoryItem*, MovieHash> MovieHash;
  typedef std::set<const InventoryItem*, MovieCompare> MovieSet;

  std::vector<Movie*> movie_list_; // holds the raw Movie data
  std::vector<const InventoryItem*> inventory_list_;
  MovieHash movie_hash_; // provides constant time lookup
  MovieSet movie_set_; // used to store movies in sorted order
  
  MovieFactory factory_; // responsible for creating movies

  static std::string get_hash_key(const InventoryItem*);
  void add_movie_to_hash(const InventoryItem*);
  void add_movie_to_set(const InventoryItem*);
};

#endif
