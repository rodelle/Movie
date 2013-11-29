#include <UnitTest++.h>
#include <iostream>

#include "../inventoryitem.h"
#include "../comedy.h"
#include "../classic.h"
#include "../drama.h"
#include "test_helper.h"

struct ZeroItems
{
  ZeroItems()
    : movie(new Comedy("Jurassic Park", "Steven Spielberg", "1993")),
      inventory(*movie)
   {}

  ~ZeroItems()
  {
    delete movie;
  }

  Movie* movie;
  InventoryItem inventory;
};

SUITE(InventoryItem_h) 
{
  TEST_FIXTURE(ZeroItems, GetMovie)
  {
    std::string expected_output = 
      "Jurassic Park   Steven Spielberg   1993";

    cout_redirect redirect;
    std::cout << inventory.movie();
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST_FIXTURE(ZeroItems, RemoveFromInventory)
  {
    inventory.AddToInventory('a', 10); // 10 remaining

    CHECK(!inventory.Contains('a', 11));
    CHECK(inventory.Contains('a', 10));
    CHECK(inventory.Contains('a', 3));
    CHECK(inventory.Contains('a', 1));

    if(inventory.Contains('a', 3))
      inventory.RemoveFromInventory('a', 3); // 7 remaining

    CHECK(inventory.GetInventoryCount('a') == 7);
    CHECK(!inventory.Contains('a', 10));
    CHECK(!inventory.Contains('a', 8));
    CHECK(inventory.Contains('a', 7));
    CHECK(inventory.Contains('a'));

    if(inventory.Contains('a'))
      inventory.RemoveFromInventory('a'); // 6 remainint

    CHECK(!inventory.Contains('a', 10));
    CHECK(!inventory.Contains('a', 7));
    CHECK(inventory.Contains('a', 6));
    CHECK(inventory.Contains('a'));
 } 

  TEST_FIXTURE(ZeroItems, AddToInventory)
  {
    // adding previously non-existent type
    inventory.AddToInventory('a'); 
    CHECK(inventory.GetInventoryCount('a') == 1);
    CHECK(inventory.GetInventoryCount('b') == 0);
    
    inventory.AddToInventory('a');
    CHECK(inventory.GetInventoryCount('a') == 2);
    CHECK(inventory.GetInventoryCount('b') == 0);

    inventory.AddToInventory('a', 5);
    CHECK(inventory.GetInventoryCount('a') == 7);
    CHECK(inventory.GetInventoryCount('b') == 0);

    // adding non-existent type, non-default amount 
    inventory.AddToInventory('b', 5); 
    CHECK(inventory.GetInventoryCount('a') == 7);
    CHECK(inventory.GetInventoryCount('b') == 5);
  }

  TEST_FIXTURE(ZeroItems, Contains_ZeroItems)
  {
    CHECK(!inventory.Contains('b'));
    CHECK(!inventory.Contains('d'));
    CHECK(!inventory.Contains('l'));
  }
}
