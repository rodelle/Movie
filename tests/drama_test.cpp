#include <UnitTest++.h>
#include <iostream>

#include "../drama.h"
#include "test_helper.h"

SUITE(Drama_h)
{
  TEST(Populate_default)
  {
    std::istringstream input("Steven Spielberg, Schindler's List, 1993");
    std::istringstream populate_input("Steven Spielberg, Schindler's List,");

    Drama drama, populated_drama;

    drama.Init(input);
    populated_drama.Populate(populate_input);

    CHECK_EQUAL(drama.title(), populated_drama.title());
    CHECK_EQUAL(drama.director(), populated_drama.director());

    CHECK(!(drama < populated_drama) && !(drama > populated_drama));
  }

  // Sorted by director then title
  TEST(OperatorLess_DirectorAndTitle)
  {
    Drama lhs("Star Wars", "George Lucas", "1977");
    Drama rhs("The Fellowship of the Ring", "Peter Jackson", "2000");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by director then title
  TEST(OperatorLess_DirectorNotTitle)
  {
    Drama lhs("Fight Club", "David Fincher", "1999");
    Drama rhs("Clue", "Jonathan Lynn", "1985");

    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  // Sorted by director then title
  TEST(OperatorLess_TitleNotDirector)
  {
    Drama lhs("Jurassic Park", "Steven Spielberg", "1993");
    Drama rhs("Star Wars", "George Lucas", "1977");

    CHECK(rhs < lhs);
    CHECK(!(rhs > lhs));

    CHECK(lhs > rhs);
    CHECK(!(lhs < rhs));
  }

  // Sorted by director then title
  TEST(OperatorLess_Equal)
  {
    Drama lhs("Jurassic Park", "Steven Spielberg", "1993");
    Drama rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(!(rhs < lhs));
    CHECK(!(rhs > lhs));

    CHECK(!(lhs > rhs));
    CHECK(!(lhs < rhs));
  }

  TEST(OperatorNotEqual_DramasNotEqual)
  {
    Drama lhs("Jurassic Park", "Steven Spielberg", "1993");
    Drama rhs("Star Wars", "George Lucas", "1977");

    CHECK(lhs != rhs);
  }

  TEST(OperatorNotEqual_DramasAreEqual)
  {
    Drama lhs("Jurassic Park", "Steven Spielberg", "1993");
    Drama rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(!(lhs != rhs));
  }

  TEST(OperatorEqual_DramasNotEqual)
  {
    Drama lhs("Jurassic Park", "Steven Spielberg", "1993");
    Drama rhs("Star Wars", "George Lucas", "1977");

    CHECK(!(lhs == rhs));
  }

  TEST(OperatorEqual_DramasAreEqual)
  {
    Drama lhs("Jurassic Park", "Steven Spielberg", "1993");
    Drama rhs("Jurassic Park", "Steven Spielberg", "1993");

    CHECK(lhs == rhs);
  }
  TEST(CopyConstructor_DefaultCase)
  {
    std::string expected_output =
      "Jurassic Park        Steven Spielberg   1993";

    Drama copied_movie("Jurassic Park", "Steven Spielberg", "1993");
    Drama movie(copied_movie);

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
    Drama movie(istream);

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
    Drama movie(istream);

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
    Drama movie(istream);

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

    Drama movie; // movie with no initialized data

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

    Drama movie("Jurassic Park", "Steven Spielberg", "1993"); // movie with initial data

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(PrintTableHeader)
  {
    Drama movie;

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
