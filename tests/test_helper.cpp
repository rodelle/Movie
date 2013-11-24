#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#include "test_helper.h"

cout_redirect::cout_redirect() 
  : old(std::cout.rdbuf(buffer.rdbuf()))
{}

std::string cout_redirect::get_output() {
  return buffer.str();
}

cout_redirect::~cout_redirect( ) { 
  std::cout.rdbuf(old);
}   

void remove_spaces(std::string& s)
{
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}
