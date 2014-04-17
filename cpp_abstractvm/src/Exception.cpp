#include "Exception.hh"

AbstractException::AbstractException(const char *msg)
{
  _msg = msg;
}

AbstractException::~AbstractException() throw()
{
}

const char	*AbstractException::what() const throw()
{
  return _msg.c_str();
}

FloatingException::FloatingException() :
  AbstractException("Floating exception : division by zero")
{
}

FloatingException::~FloatingException() throw()
{
}

MemoryEmptyException::MemoryEmptyException() :
  AbstractException("Memory is empty")
{
}

MemoryEmptyException::~MemoryEmptyException() throw()
{
}

SyntaxException::SyntaxException() :
  AbstractException(SYNTAX_ERROR)
{
}

SyntaxException::~SyntaxException() throw()
{
}

BadInstException::BadInstException() :
  AbstractException(UNKNOWN_INSTRUCTION)
{
}

BadInstException::~BadInstException() throw()
{
}

OverFlowException::OverFlowException() :
  AbstractException("OverFlow Detected")
{
}

OverFlowException::~OverFlowException() throw()
{
}

UnderFlowException::UnderFlowException() :
  AbstractException("UnderFlow Detected")
{
}

UnderFlowException::~UnderFlowException() throw()
{
}
