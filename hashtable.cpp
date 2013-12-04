#include <vector>
#include <cstddef>

#include "hashtable.h"

const int HashTable::kDefaultSize = 10000;

HashTable::HashTable()
{
  data_.resize(kDefaultSize);

  // initialize the default values of the array
  for(int i = 0; i < kDefaultSize; ++i)
    data_[i] = NULL;
}

HashTable::~HashTable()
{
  // initialize the default values of the array
  for(int i = 0; i < kDefaultSize; ++i)
    delete data_[i];
}

std::size_t HashTable::calculate_hash(const K& key) const
{
  return static_cast<std::size_t>(key);
}

HashTable::const_iterator HashTable::end() const
{
  return NULL;
}

// returns an iterator to the element if the element is found
// otherwise, it returns an iterator to HashTable::end
// (the element past the end of the container)
HashTable::const_iterator HashTable::find(const K& key) const
{
  std::size_t hash = calculate_hash(key);
  return data_[hash];
}

#include <iostream>

// inserts the element into the hash table
void HashTable::insert(const K& key, const V& value)
{
  std::cout << "Inserting!\n";
  std::size_t hash = calculate_hash(key);

  if(data_[hash] != NULL) // already exists
    return;

  V* insert = new V(value);
  data_[hash] = insert;
}

