#include "loader.hpp"

DLLoadingException::DLLoadingException(const char *msg)
{
  _msg = msg;
}

DLLoadingException::~DLLoadingException() throw()
{
}

const char*	DLLoadingException::what() const throw()
{
  return _msg.c_str();
}
