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
  add_movie_to_set(movieType, item);
}

void MovieCollection::add_movie_to_set(const char movieType, InventoryItem* item)
{
  movie_set_[movieType].insert(item);
/*  for(MovieSet::iterator i = movie_set_[movieType].begin(); i != movie_set_[movieType].end(); ++i)
    std::cout << "Tree Movie:  " << (*i)->movie() << std::endl;
    */
}

void MovieCollection::add_movie_to_hash(InventoryItem* item)
{
  std::string movie_key = MovieCollection::get_hash_key(inventory_list_.back()->movie());

  typedef std::pair<std::string, InventoryItem*> MovieHashPair;
  MovieHashPair hash_element(movie_key, item);

  movie_hash_.insert(hash_element);
}

InventoryItem* MovieCollection::GetMovie(std::istream& input) const
{
  char movieType;
  input >> movieType;

  if(input.fail()) // invalid input
    return NULL;

  Movie* movie = factory_.InstanceOf(movieType);

  if(movie == NULL)
    return NULL;

  movie->Populate(input); // fill the fields with the search criteria

  InventoryItem* hash_result = this->search_in_hash(*movie);

  if(hash_result != NULL)
    return hash_result;

  return this->search_in_set(movieType, *movie);
}

InventoryItem* MovieCollection::search_in_set(
  const char movieType,
  const Movie& movie) const
{
  MovieSetHash::const_iterator sh_iter = movie_set_.find(movieType);

  if(sh_iter == movie_set_.end()) // no movies of this type exist
    return NULL;

  const MovieSet& movie_set = sh_iter->second;

  InventoryItem item(movie);
  MovieSet::const_iterator set_iter = movie_set.find(&item);

  if(set_iter != movie_set.end()) // found in set, return InventoryItem
    return *set_iter;

  return NULL; // movie not found in set
}

InventoryItem* MovieCollection::search_in_hash(const Movie& movie) const
{
  std::string movie_key = MovieCollection::get_hash_key(movie);
  MovieHash::const_iterator hash_iter = movie_hash_.find(movie_key);

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

boost::hash<std::string> MovieCollection::StringHash::string_hash;

std::size_t MovieCollection::StringHash::operator() (
  const std::string& key) const
{
  return MovieCollection::StringHash::string_hash(key);
}

std::size_t MovieCollection::CharHash::operator() (
  const char c) const
{
  return c - 'A';
}

const MovieCollection::MovieSetHash& MovieCollection::GetAllMovies() const
{
  return movie_set_;
}
