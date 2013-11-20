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


SUITE(Output)
{
  TEST_FIXTURE(MovieSetup, MovieWithEmptyData_output)
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

  TEST_FIXTURE(MovieSetup, MovieWithData_output)
  {
    std::string expected_output = 
      "Jurassic Park        George Lucas";

    Movie movie("Jurassic Park", "George Lucas"); // movie with initial data

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
