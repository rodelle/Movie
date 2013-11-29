#include "mcollection.h"

MovieCollection::MovieCollection()
{}

MovieCollection::~MovieCollection()
{
  std::vector<Movie*>::iterator i;
  for(i = movie_list_.begin(); i != movie_list_.end(); ++i) {
    delete *i;
  }
}

void MovieCollection::AddMovie(std::istream& input)
{
  char type;
  input >> type;
  Movie* movie = factory_.Create(type);
  if(movie != NULL) {
    movie->Init(input);
    movie_list_.push_back(movie);
  }
}

/*
InventoryItem MovieCollection::GetMovie(std::istream& input)
{
  re
}
*/

bool MovieCollection::MovieCompare::operator() (
  const InventoryItem& lhs, 
  const InventoryItem& rhs) const
{
  return lhs.movie() < rhs.movie(); 
}

boost::hash<std::string> MovieCollection::MovieHash::string_hash;

std::size_t MovieCollection::MovieHash::operator() (
  const InventoryItem& item) const
{
  std::string key = item.movie().title() + item.movie().director();
  return MovieCollection::MovieHash::string_hash(key);
}
