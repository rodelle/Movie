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
      "Jurassic Park   Steven Spielber   1993";

    cout_redirect redirect;
    std::cout << inventory.movie();
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST_FIXTURE(ZeroItems, RemoveFromInventory_default)
  {
    inventory.AddToInventory(10); // 10 remaining

    CHECK(!inventory.Contains(11));
    CHECK(inventory.Contains(10));
    CHECK(inventory.Contains(3));
    CHECK(inventory.Contains(1));

    if(inventory.Contains(3))
      inventory.RemoveFromInventory(3); // 7 remaining

    CHECK(inventory.GetInventoryCount() == 7);
    CHECK(!inventory.Contains(10));
    CHECK(!inventory.Contains(8));
    CHECK(inventory.Contains(7));
    CHECK(inventory.Contains());

    if(inventory.Contains())
      inventory.RemoveFromInventory(); // 6 remainint

    CHECK(!inventory.Contains(10));
    CHECK(!inventory.Contains(7));
    CHECK(inventory.Contains(6));
    CHECK(inventory.Contains());
 }

  TEST_FIXTURE(ZeroItems, AddToInventory)
  {
    // adding previously non-existent type
    inventory.AddToInventory();
    CHECK(inventory.GetInventoryCount() == 1);
    CHECK(inventory.GetInventoryCount('b') == 0);

    inventory.AddToInventory();
    CHECK(inventory.GetInventoryCount() == 2);
    CHECK(inventory.GetInventoryCount('b') == 0);

    inventory.AddToInventory(5);
    CHECK(inventory.GetInventoryCount() == 7);
    CHECK(inventory.GetInventoryCount('b') == 0);

    // adding non-existent type, non-default amount
    inventory.AddToInventory(5, 'b');
    CHECK(inventory.GetInventoryCount() == 7);
    CHECK(inventory.GetInventoryCount('b') == 5);
  }

  TEST_FIXTURE(ZeroItems, Contains_ZeroItems)
  {
    CHECK(!inventory.Contains('b'));
    CHECK(!inventory.Contains('d'));
    CHECK(!inventory.Contains('l'));
  }
}
