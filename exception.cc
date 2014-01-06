#include <new>
#include "exception.hh"
#include <iostream>

MyException::MyException(const char *error) throw()
  : ErrorString(error)
{}

MyException::MyException(const std::string error) throw()
  : ErrorString(error)
{}

MyException::MyException() throw()
  : ErrorString(std::string(""))
{}
MyException::~MyException() throw()
{}
const char *MyException::what() const throw() {
  return ErrorString.c_str();
}

void MyException::report(const char*origin) const throw() {
  if(!(ErrorString.empty())) {
    if (NULL==origin)
      std::cerr << "MyException: " << ErrorString << std::endl;
    else
      std::cerr << "[ " << origin << "]: " << ErrorString << std::endl;
  }
}


void gem::catchMyException(const char*name) {
  try {
    throw;
  } catch (MyException&ex) {
      ex.report(name);
  }
}
