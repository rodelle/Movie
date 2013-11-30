#include "inventoryitem.h"

const char InventoryItem::kDefaultMediaType = 'd'; 

std::size_t InventoryItem::CharHash::operator() (char c) const
{
  return c - 'a';
}

InventoryItem::InventoryItem(const Movie& movie)
  : movie_(movie)
{}

const Movie& InventoryItem::movie() const
{
  return movie_;
}

void InventoryItem::RemoveFromInventory(const int amount, const char mediaType)
{
  if(inventory_.count(mediaType) == 0) // media type does not exist
    return; // throw exception 

  inventory_[mediaType] -= amount;
} 

void InventoryItem::AddToInventory(const int amount, const char mediaType)
{
   if(inventory_.count(mediaType) == 0) { // media type does not exist
     std::pair<char, int> mediaInventory(mediaType, 0);
     inventory_.insert(mediaInventory);
   }

  inventory_[mediaType] += amount;
}

int InventoryItem::GetInventoryCount(const char mediaType)
{
  if(inventory_.count(mediaType) == 0) // media type does not exist
    return 0; 

  return inventory_[mediaType]; 
}


bool InventoryItem::Contains(const int orderSize, const char mediaType)
{
  if(inventory_.count(mediaType) == 0)
    return false;

  return inventory_[mediaType] >= orderSize;
}
