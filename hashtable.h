///////////////////////////////////////////////////////////////////////////////
// HashTable.h
// Represents an unordered container of key-value pairs. HashTables provide
// constant time insertion and lookup of elements by their key.
///////////////////////////////////////////////////////////////////////////////

#ifndef CSS343_LAB4_HASHTABLE_H
#define CSS343_LAB4_HASHTABLE_H

class StoreCustomer;

class HashTable
{
public:
  typedef int K; // key
  typedef StoreCustomer* const V; // value
  typedef V* const_iterator;

  HashTable();
  ~HashTable();

  // returns an iterator to the element if the element is found
  // otherwise, it returns an iterator to HashTable::end
  // (the element past the end of the container)
  const_iterator find(const K&) const;

  // Returns an iterator to the element one past the end of the container
  const_iterator end() const;

  // inserts the element into the hash table
  void insert(const K&, const V&);

private:
  static const int kDefaultSize;
  std::size_t calculate_hash(const K&) const; // calculates the has given the key value
  std::vector<V*> data_;
};

#endif
