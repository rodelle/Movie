#include <UnitTest++.h>
#include <iostream>

#include "../classic.h"
#include "test_helper.h"

SUITE(Classic_h)
{
  TEST(Populate_default)
  {
    std::istringstream input("George Cukor, Holiday, Katherine Hepburn 9 1938");
    std::istringstream populate_input("9 1938 Katherine Hepburn");

    Classic classic, populated_classic;

    classic.Init(input);
    populated_classic.Populate(populate_input);

    CHECK_EQUAL(classic.month(), populated_classic.month());
    CHECK_EQUAL(classic.year(), populated_classic.year());
    CHECK_EQUAL(classic.actor(), populated_classic.actor());

    CHECK(!(classic < populated_classic) && !(classic > populated_classic));
  }

  // Sorted by date then famous actor
  TEST(OperatorLess_DateAndActor)
  {
    Classic lhs("Holiday", "George Cukor", "Katherine Hepburn 9 1938");
    Classic rhs("Harold and Maude", "Hal Ashby", "Ruth Gordan 2 1971");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by date then famous actor
  TEST(OperatorLess_YearNotMonth)
  {
    Classic lhs("Holiday", "George Cukor", "Katherine Hepburn 2 1938");
    Classic rhs("Harold and Maude", "Hal Ashby", "Ruth Gordan 7 1938");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by date then famous actor
  TEST(OperatorLess_ActorNotYear)
  {
    Classic lhs("Holiday", "George Cukor", "Katherine Hepburn 7 1971");
    Classic rhs("Harold and Maude", "Hal Ashby", "Ruth Gordan 2 1938");

    CHECK(rhs < lhs);
    CHECK(!(rhs > lhs));

    CHECK(lhs > rhs);
    CHECK(!(lhs < rhs));
  }

  // Sorted by date then famous actor
  TEST(OperatorLess_Equal)
  {
    Classic lhs("Holiday", "George Cukor", "Katherine Hepburn 9 1938");
    Classic rhs("Holiday", "George Cukor", "Katherine Hepburn 9 1938");

    CHECK(!(rhs < lhs));
    CHECK(!(rhs > lhs));

    CHECK(!(lhs > rhs));
    CHECK(!(lhs < rhs));
  }


  TEST(OperatorEqual_ClassicsNotEqual)
  {
    Classic lhs("Holiday", "George Cukor", "Katherine Hepburn 9 1938");
    Classic rhs("Harold ad Maude", "Hal Ashby", "Ruth Gordan 2 1971");

    CHECK(!(lhs == rhs));
    CHECK(lhs != rhs);
  }

  TEST(OperatorEqual_ClassicsAreEqual)
  {
    Classic lhs("Holiday", "George Cukor", "Katherine Hepburn 9 1938");
    Classic rhs("Holiday", "George Cukor", "Katherine Hepburn 9 1938");

    CHECK(lhs == rhs);
    CHECK(!(lhs != rhs));
  }

  TEST(CopyConstructor_DefaultCase)
  {
    std::string expected_output =
      "Holiday   George Cukor  9 1938  Katherine Hepburn";

    Classic copied_movie("Holiday", "George Cukor", "Katherine Hepburn 9 1938");
    Classic movie(copied_movie);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(IStreamConstructor_DefaultCase)
  {
    std::string input =
      "George Cukor, Holiday, Katherine Hepburn 9 1938";

    std::string expected_output =
      "Holiday   George Cukor  9 1938  Katherine Hepburn";

    std::istringstream istream(input);
    Classic movie(istream);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(Constructor_DefaultCase)
  {
    std::string expected_output =
      "Holiday   George Cukor  9 1938  Katherine Hepburn";

    Classic movie("Holiday", "George Cukor", "Katherine Hepburn 9 1938");

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(IStreamConstructor_EmptyData)
  {
    std::string expected_output =
      "1 1800";

    std::istringstream istream;
    Classic movie(istream);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(IStreamConstructor_PartialData)
  {
    std::string input =
      "Jurassic Park";

    // fails on incomplete data
    std::string expected_output =
      "1 1800";

    std::istringstream istream(input);
    Classic movie(istream);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(Constructor_EmptyData)
  {
    std::string expected_output =
      "1 1800";

    Classic movie; // movie with no initialized data

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }


  TEST(PrintTableHeader)
  {
    Classic movie;

    std::string expected_output =
      "TITLE   DIRECTOR   MO  YEAR  MAJOR ACTOR";

    cout_redirect redirect;
    movie.PrintTableHeader();
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}
