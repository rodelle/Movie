#include "inventoryitem.h"

const char InventoryItem::kDefaultMediaType = 'D';
const char* InventoryItem::kDefaultMediaName = "DVD";

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

  inventory_[mediaType].remaining -= amount;
}

void InventoryItem::AddToRemaining(const int amount, const char mediaType)
{
  if(inventory_.count(mediaType) == 0) { // media type does not exist
    return;
  }

  inventory_[mediaType].remaining += amount;
}

void InventoryItem::AddToTotal(const int amount, const char mediaType)
{
  if(inventory_.count(mediaType) == 0) { // media type does not exist
    Inventory inventory;
    inventory.total = 0;
    inventory.remaining = 0;
    std::pair<char, Inventory> mediaInventory(mediaType, inventory);
    inventory_.insert(mediaInventory);
  }

  inventory_[mediaType].total += amount;
  inventory_[mediaType].remaining += amount;
}

int InventoryItem::GetTotal(const char mediaType) const
{
  if(inventory_.count(mediaType) == 0) // media type does not exist
    return 0;

  return inventory_.find(mediaType)->second.total;
}

int InventoryItem::GetRemaining(const char mediaType) const
{
  if(inventory_.count(mediaType) == 0) // media type does not exist
    return 0;

  return inventory_.find(mediaType)->second.remaining;
}

bool InventoryItem::Contains(const int orderSize, const char mediaType) const
{
  if(inventory_.count(mediaType) == 0)
    return false;

  return inventory_.find(mediaType)->second.remaining >= orderSize;
}
