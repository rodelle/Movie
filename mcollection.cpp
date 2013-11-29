#include "mcollection.h"
#include <iostream>

MovieCollection::MovieCollection()
{}

MovieCollection::~MovieCollection()
{
  std::vector<Movie*>::iterator i;
  for(i = movie_list_.begin(); i != movie_list_.end(); ++i) {
    delete *i;
  }

  std::vector<InventoryItem const*>::iterator j;
  for(j = inventory_list_.begin(); j != inventory_list_.end(); ++j) {
    delete *j;
  }
}

void MovieCollection::AddMovie(std::istream& input)
{
  char type;
  input >> type;
  Movie* movie = factory_.Create(type);

  if(movie == NULL)
    return;

  movie->Init(input);
  movie_list_.push_back(movie);
  inventory_list_.push_back(new InventoryItem(*movie));
  
  std::cout << *movie_list_.back() << std::endl;

  add_movie_to_hash(inventory_list_.back());
  add_movie_to_set(inventory_list_.back());
}

void MovieCollection::add_movie_to_set(const InventoryItem* item)
{
  movie_set_.insert(item);
}

void MovieCollection::add_movie_to_hash(const InventoryItem* item)
{
  std::string movie_key = MovieCollection::get_hash_key(inventory_list_.back());

  typedef std::pair<std::string, const InventoryItem*> MovieHashPair;
  MovieHashPair hash_element(
    movie_key, 
    inventory_list_.back()); // inserts newly created InventoryItem

  movie_hash_.insert(hash_element);
  std::cout << movie_hash_[movie_key]->movie() << std::endl;
}

/*
InventoryItem MovieCollection::GetMovie(std::istream& input)
{
  re
}
*/

bool MovieCollection::MovieCompare::operator() (
  const InventoryItem* lhs, 
  const InventoryItem* rhs) const
{
  return lhs->movie() < rhs->movie(); 
}

std::string MovieCollection::get_hash_key(const InventoryItem* item)
{
  return item->movie().title() + item->movie().director();
}

boost::hash<std::string> MovieCollection::MovieHash::string_hash;

std::size_t MovieCollection::MovieHash::operator() (
  const std::string& key) const
{
  return MovieCollection::MovieHash::string_hash(key);
}
