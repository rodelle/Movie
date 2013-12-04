#include <UnitTest++.h>
#include <iostream>

#include "../comedy.h"
#include "test_helper.h"

SUITE(Comedy_h)
{
  TEST(Populate_default)
  {
    std::istringstream input("Gore Verbinski, Pirates of the Caribbean, 2003");
    std::istringstream populate_input("Pirates of the Caribbean, 2003");

    Comedy comedy, populated_comedy;

    comedy.Init(input);
    populated_comedy.Populate(populate_input);

    CHECK_EQUAL(comedy.title(), populated_comedy.title());
    CHECK_EQUAL(comedy.year(), populated_comedy.year());

    CHECK(!(comedy < populated_comedy) && !(comedy > populated_comedy));
  }

  // Sorted by title then date
  TEST(OperatorLess_TitleAndDate)
  {
    Comedy lhs("Star Wars", "George Lucas", "1977");
    Comedy rhs("The Fellowship of the Ring", "Peter Jackson", "2000");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by title then date
  TEST(OperatorLess_TitleNotDate)
  {
    Comedy lhs("Fight Club", "David Finchr", "1999");
    Comedy rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by title then date
  TEST(OperatorLess_DateNotTitle)
  {
    Comedy lhs("Jurassic Park", "Steven Spielberg", "1993");
    Comedy rhs("Star Wars", "George Lucas", "1977");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by title then date
  TEST(OperatorLess_Equal)
  {
    Comedy lhs("Jurassic Park", "Steven Spielberg", "1993");
    Comedy rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(!(rhs < lhs));
    CHECK(!(rhs > lhs));

    CHECK(!(lhs > rhs));
    CHECK(!(lhs < rhs));
  }

  TEST(OperatorNotEqual_ComedysNotEqual)
  {
    Comedy lhs("Jurassic Park", "Steven Spielberg", "1993");
    Comedy rhs("Star Wars", "George Lucas", "1977");

    CHECK(lhs != rhs);
  }

  TEST(OperatorNotEqual_ComedysAreEqual)
  {
    Comedy lhs("Jurassic Park", "Steven Spielberg", "1993");
    Comedy rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(!(lhs != rhs));
  }

  TEST(OperatorEqual_ComedysNotEqual)
  {
    Comedy lhs("Jurassic Park", "Steven Spielberg", "1993");
    Comedy rhs("Star Wars", "George Lucas", "1977");

    CHECK(!(lhs == rhs));
  }

  TEST(OperatorEqual_ComedysAreEqual)
  {
    Comedy lhs("Jurassic Park", "Steven Spielberg", "1993");
    Comedy rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(lhs == rhs);
  }
  TEST(CopyConstructor_DefaultCase)
  {
    std::string expected_output =
      "Jurassic Park        Steven Spielberg   1993";

    Comedy copied_movie("Jurassic Park", "Steven Spielberg", "1993"); // movie with no initialized data
    Comedy movie(copied_movie);

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
      "Steven Spielberg, Jurassic Park, 1993";

    std::string expected_output =
      "Jurassic Park        Steven Spielberg    1993";

    std::istringstream istream(input);
    Comedy movie(istream);

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
      "1800";

    std::istringstream istream;
    Comedy movie(istream);

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
      "1800";

    std::istringstream istream(input);
    Comedy movie(istream);

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
      "1800";

    Comedy movie; // movie with no initialized data

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
      "Jurassic Park        Steven Spielberg   1993";

    Comedy movie("Jurassic Park", "Steven Spielberg", "1993"); // movie with initial data

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(PrintTableHeader)
  {
    Comedy movie;

    std::string expected_output =
      "TITLE   DIRECTOR   YEAR";

    cout_redirect redirect;
    movie.PrintTableHeader(std::cout);
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}
