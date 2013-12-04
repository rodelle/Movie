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
private:
  struct MovieCompare
  {
    bool operator() (const InventoryItem*, const InventoryItem*) const;
  };

  struct CharHash
  {
    std::size_t operator() (const char) const;
  };

public:
  MovieCollection();
  ~MovieCollection();

  // 10 new copies of the movie are added to the store’s inventory.
  // format: movieType director director, title title, additional information
  void AddMovie(std::istream&);

  // Retrieves previously added movies from the collection. If the identifier can be mapped
  // to a unique movie, the complexity of this call is O(1). If the identifier cannot be mapped
  // to a unique movie, the complexity of this call is O(logN).
  InventoryItem* GetMovie(std::istream&) const;

  typedef std::set<InventoryItem*, MovieCompare> MovieSet;

  typedef std::tr1::unordered_map
    <char, MovieSet, CharHash>
    MovieSetHash;

  const MovieSetHash& GetAllMovies() const;

private:

  struct StringHash
  {
    std::size_t operator() (const std::string&) const;
    static boost::hash<std::string> string_hash;
  };

  typedef std::tr1::unordered_map
    <std::string, InventoryItem*, StringHash>
    MovieHash;

  std::vector<const Movie*> movie_list_; // holds the raw Movie data
  std::vector<InventoryItem*> inventory_list_;
  MovieHash movie_hash_; // provides constant time lookup
  MovieSetHash movie_set_; // used to store movies in sorted order

  MovieFactory factory_; // responsible for creating movies

  static std::string get_hash_key(const Movie&);

  // Searches for the given movie in the hash list of movies
  // Returns the InventoryItem is found, otherwise returns NULL
  InventoryItem* search_in_hash(const Movie&) const;

  // Searches for the given movie in the previously stored set of movies
  // Returns the InventoryItem is found, otherwise returns NULL
  // @param movieGenre - the genre of the movie to search for
  InventoryItem* search_in_set(const char, const Movie&) const;

  void add_movie_to_hash(InventoryItem*);
  void add_movie_to_set(const char, InventoryItem*);

  // The number of movies the inventoy is incrased by
  static const int kDefaultAddCount;
};

#endif
