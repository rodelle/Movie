// test_shortestpath.cpp

#include <UnitTest++.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "../movie.h"

struct cout_redirect {
  cout_redirect() 
    :  old(std::cout.rdbuf(buffer.rdbuf()))
  {}

  std::string get_output() {
    return buffer.str();
  }

  ~cout_redirect( ) { 
    std::cout.rdbuf(old);
  }   

private:
  std::streambuf* old;
  std::stringstream buffer;
};

void remove_spaces(std::string& s)
{
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

SUITE(OperatorEquality) 
{
  TEST(LeftLessThanRight)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg");
    Movie rhs("Star Wars", "George Lucas"); 
     
    CHECK(lhs < rhs);
    CHECK(!(lhs > rhs));

    CHECK(rhs > lhs);
    CHECK(!(rhs < lhs));
  }

  TEST(OperatorNotEqual_MoviesNotEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg");
    Movie rhs("Star Wars", "George Lucas"); 
     
    CHECK(lhs != rhs);
  }

  TEST(OperatorNotEqual_MoviesAreEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg");
    Movie rhs("Jurassic Park", "Steven Spielberg");
     
    CHECK(!(lhs != rhs));
  } 

  TEST(OperatorEqual_MoviesNotEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg");
    Movie rhs("Star Wars", "George Lucas"); 
     
    CHECK(!(lhs == rhs));
  }

  TEST(OperatorEqual_MoviesAreEqual)
  {
    Movie lhs("Jurassic Park", "Steven Spielberg");
    Movie rhs("Jurassic Park", "Steven Spielberg"); 
     
    CHECK(lhs == rhs);
  }
}


SUITE(OperatorEqual) 
{
  TEST(DefaultCase)
  {
    std::string expected_output = 
      "Jurassic Park        Steven Spielberg";

    Movie copied_movie("Jurassic Park", "Steven Spielberg"); // movie with no initialized data
    Movie movie = copied_movie;

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}

SUITE(CopyConstructor) 
{
  TEST(DefaultCase)
  {
    std::string expected_output = 
      "Jurassic Park        Steven Spielberg";

    Movie copied_movie("Jurassic Park", "Steven Spielberg"); // movie with no initialized data
    Movie movie(copied_movie);

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}

SUITE(Output)
{
  TEST(MovieWithEmptyData_output)
  {
    std::string expected_output = 
      "";

    Movie movie; // movie with no initialized data

    cout_redirect redirect;
    std::cout << movie;
    std::string program_output = redirect.get_output();
 
    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }

  TEST(MovieWithData_output)
  {
    std::string expected_output = 
      "Jurassic Park        Steven Spielberg";

    Movie movie("Jurassic Park", "Steven Spielberg"); // movie with initial data

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
      "TITLE   DIRECTOR";

    cout_redirect redirect;
    movie.PrintTableHeader(); 
    std::string program_output = redirect.get_output();

    remove_spaces(program_output);
    remove_spaces(expected_output);

    CHECK_EQUAL(expected_output, program_output);
  }
}

int main()
{
  return UnitTest::RunAllTests();
}
