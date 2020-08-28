
#include <foobar/mylib.hpp>

#include <iostream>


auto main() -> int
{
  foobar::log_setup(foobar::log_configuration{});

  std::cout << "Hello World" << std::endl;
  MYLOG_DEBUG("Hello", "World")
  MYLOG_DEBUG("Hello", "World")
  MYLOG_DEBUG("Hello", "World")
  MYLOG_DEBUG("Hello", "World")
  return 0;
}