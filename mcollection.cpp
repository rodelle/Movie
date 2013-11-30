#include "mcollection.h"
#include <iostream>

const int MovieCollection::kDefaultAddCount = 10;

MovieCollection::MovieCollection()
{}

MovieCollection::~MovieCollection()
{
  std::vector<const Movie*>::iterator i;
  for(i = movie_list_.begin(); i != movie_list_.end(); ++i) {
    delete *i;
  }

  std::vector<InventoryItem*>::iterator j;
  for(j = inventory_list_.begin(); j != inventory_list_.end(); ++j) {
    delete *j;
  }
}

void MovieCollection::AddMovie(std::istream& input)
{
  char movieType;
  input >> movieType;

  if(input.fail())
    return;

  Movie* movie = factory_.Create(movieType);

  if(movie == NULL)
    return;

  movie->Init(input);
  
  InventoryItem* item = this->search_in_hash(*movie);

  if(item == NULL) { // movie does not exist in hash 
    movie_list_.push_back(movie);
    inventory_list_.push_back(new InventoryItem(*movie));
    item = inventory_list_.back();
    add_movie_to_hash(item);
  } else {
    delete movie; // no longer needed
  }

  item->AddToInventory(kDefaultAddCount); // increase the existing stock
  add_movie_to_set(item);
}

void MovieCollection::add_movie_to_set(InventoryItem* item)
{
  movie_set_.insert(item);
}

void MovieCollection::add_movie_to_hash(InventoryItem* item)
{
  std::string movie_key = MovieCollection::get_hash_key(inventory_list_.back()->movie());

  typedef std::pair<std::string, InventoryItem*> MovieHashPair;
  MovieHashPair hash_element(movie_key, item);

  movie_hash_.insert(hash_element);
}

InventoryItem* MovieCollection::GetMovie(std::istream& input)
{
  char movieType, mediaType;
  input >> mediaType >> movieType;

  if(input.fail()) // invalid input
    return NULL;

  Movie* movie = factory_.InstanceOf(movieType);

  if(movie == NULL)
    return NULL;

  movie->Populate(input); // fill the fields with the search criteria

  InventoryItem* hash_result = this->search_in_hash(*movie);

  if(hash_result != NULL)
    return hash_result;

  return this->search_in_set(*movie);
}

InventoryItem* MovieCollection::search_in_set(const Movie& movie)
{
  InventoryItem item(movie);
  MovieSet::iterator set_iter = movie_set_.find(&item);

  if(set_iter != movie_set_.end()) // found in set, return InventoryItem
    return *set_iter;
 
  return NULL; // movie not found in set
}

InventoryItem* MovieCollection::search_in_hash(const Movie& movie)
{
  std::string movie_key = MovieCollection::get_hash_key(movie);
  MovieHash::iterator hash_iter = movie_hash_.find(movie_key);

  if(hash_iter != movie_hash_.end()) // found in hash set, return InventoryItem
    return hash_iter->second;
 
  return NULL; // movie cannot be mapped to movie in hash set
}

bool MovieCollection::MovieCompare::operator() (
  const InventoryItem* lhs, 
  const InventoryItem* rhs) const
{
  return lhs->movie() < rhs->movie(); 
}

std::string MovieCollection::get_hash_key(const Movie& movie)
{
  return movie.title() + movie.director();
}

boost::hash<std::string> MovieCollection::MovieHash::string_hash;

std::size_t MovieCollection::MovieHash::operator() (
  const std::string& key) const
{
  return MovieCollection::MovieHash::string_hash(key);
}
