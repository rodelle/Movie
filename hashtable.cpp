#include <vector>
#include <cstddef>

#include "hashtable.h"

const int HashTable::kDefaultSize = 10000;

HashTable::HashTable()
  : tablesize_(kDefaultSize)
{
  data_.resize(tablesize_);

  // initialize the default values of the array
  for(std::size_t i = 0; i < tablesize_; ++i)
    data_[i] = NULL;
}

HashTable::~HashTable()
{
  // clear any memory allocated
  for(std::size_t i = 0; i < tablesize_; ++i) {
    if(data_[i] != NULL)
      delete data_[i];
  }
}

std::size_t HashTable::calculate_hash(const K& key) const
{
  return static_cast<std::size_t>(key);
}

// used to return a hash value that can be safely used as an index in data_
std::size_t HashTable::sanitize_hash(const K& key) const
{
  std::size_t hash = calculate_hash(key);
  if(hash < 0) // modulus by a negative number is not well defined
    hash *= -1; // can lead to unexpected collisions

  if(hash != 0) // prevent division by 0
    hash =  hash % tablesize_;

  return hash;
}

// NULL pointer is used to indicate that an element does not exist
HashTable::const_iterator HashTable::end() const
{
  return NULL;
}

// returns the data stored at data_[hash(key)]
// since data_ is storing pointers to the Value type, dereferencing it will
// return the value (similiar behavior to iterators). The returned iterator/
// pointer only supports lookup, and does not allow traversal
HashTable::const_iterator HashTable::find(const K& key) const
{
  std::size_t hash = sanitize_hash(key);
  // collisions are not handled
  return data_[hash];
}

// inserts the element into the hash table
void HashTable::insert(const K& key, const V& value)
{
  std::size_t hash = sanitize_hash(key);
  if(data_[hash] != NULL) // already exists
    return;

  V* insert = new V(value); // uses V's copy constructor
  data_[hash] = insert; // insert the element into the
}

