#include <UnitTest++.h>
#include <iostream>

#include "../movie.h"
#include "test_helper.h"

SUITE(OperatorEquality) 
{
  TEST(LeftLessThanRight)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg", 1993);
    Movie rhs("Star Wars", "George Lucas", 1977); 
     
    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  TEST(OperatorNotEqual_MoviesNotEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg", 1993);
    Movie rhs("Star Wars", "George Lucas", 1977); 
     
    CHECK(lhs != rhs);
  }

  TEST(OperatorNotEqual_MoviesAreEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg", 1993);
    Movie rhs("Jurassic Park", "Steven Spielberg", 1993);
     
    CHECK(!(lhs != rhs));
  } 

  TEST(OperatorEqual_MoviesNotEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg", 1993);
    Movie rhs("Star Wars", "George Lucas", 1977); 
     
    CHECK(!(lhs == rhs));
  }

  TEST(OperatorEqual_MoviesAreEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg", 1993);
    Movie rhs("Jurassic Park", "Steven Spielberg", 1993); 
     
    CHECK(lhs == rhs);
  }
}

/*
SUITE(Constructor) 
{
  TEST(Constructor_DefaultCase)
  {
    std::string expected_output = 
      "Jurassic Park        Steven Spielberg   1993";

    Movie copied_movie("Jurassic Park", "Steven Spielberg", 1993); // movie with no initialized data
    Movie movie = copied_movie;

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}
*/

SUITE(CopyConstructor) 
{
  TEST(CopyConstructor_DefaultCase)
  {
    std::string expected_output = 
      "Jurassic Park        Steven Spielberg   1993";

    Movie copied_movie("Jurassic Park", "Steven Spielberg", 1993); // movie with no initialized data
    Movie movie(copied_movie);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}

SUITE(IStreamConsructor)
{
  TEST(IStreamConstructor_DefaultCase)
  {
    std::string input = 
      "Jurassic Park, Steven Spielberg, 1993";
    
    std::string expected_output = 
      "Jurassic Park        Steven Spielberg    1993";

    std::istringstream istream(input);
    Movie movie(istream);

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
    Movie movie(istream);

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
    Movie movie(istream);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  } 

}

SUITE(Constructor)
{
  TEST(Constructor_EmptyData)
  {
    std::string expected_output = 
      "1800";

    Movie movie; // movie with no initialized data

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

    Movie movie("Jurassic Park", "Steven Spielberg", 1993); // movie with initial data

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}

SUITE(TableHeader)
{
  TEST(PrintTableHeader_output)
  {
    Movie movie;
    
    std::string expected_output = 
      "TITLE   DIRECTOR   YEAR";

    cout_redirect redirect;
    movie.PrintTableHeader(); 
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}
