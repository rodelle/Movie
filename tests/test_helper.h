#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string>

struct cout_redirect
{
  cout_redirect();
  ~cout_redirect();
  std::string get_output();

private:
  std::streambuf* old;
  std::stringstream buffer;
};

void remove_spaces(std::string& s);

#endif
