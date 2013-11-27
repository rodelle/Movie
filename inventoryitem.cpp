#include "inventoryitem.h"

const char InventoryItem::kDefaultMediaType = 'd'; 

std::size_t InventoryItem::CharHash::operator() (char c) const
{
  return c - 'a';
}

InventoryItem::InventoryItem(const Movie& movie)
  : movie_(movie)
{}

const Movie& InventoryItem::movie()
{
  return movie_;
}

void InventoryItem::RemoveFromInventory(char mediaType, int amount)
{
  if(inventory_.count(mediaType) == 0) // media type does not exist
    return; // throw exception 

  inventory_[mediaType] -= amount;
} 

void InventoryItem::AddToInventory(char mediaType, int amount)
{
   if(inventory_.count(mediaType) == 0) { // media type does not exist
     std::pair<char, int> mediaInventory(mediaType, 0);
     inventory_.insert(mediaInventory);
   }

  inventory_[mediaType] += amount;
}

int InventoryItem::GetInventoryCount(char mediaType)
{
  if(inventory_.count(mediaType) == 0) // media type does not exist
    return 0; 

  return inventory_[mediaType]; 
}


bool InventoryItem::Contains(char mediaType, int orderSize)
{
  if(inventory_.count(mediaType) == 0)
    return false;

  return inventory_[mediaType] >= orderSize;
}
