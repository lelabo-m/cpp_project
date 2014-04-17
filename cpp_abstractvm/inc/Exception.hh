#ifndef EXCEPTION_HH_
# define EXCEPTION_HH_

#include <exception>
#include <string>

/*
** Errors
*/

# define UNKNOWN_INSTRUCTION "Undefinded instruction."
# define SYNTAX_ERROR "Error de sintaxis."

class AbstractException : public std::exception
{
public:
  AbstractException(const char *msg = "");
  virtual ~AbstractException() throw();
  const char *	what() const throw();
private:
  std::string	_msg;
};

class FloatingException : public AbstractException
{
public:
  FloatingException();
  ~FloatingException() throw();
};

class MemoryEmptyException : public AbstractException
{
public:
  MemoryEmptyException();
  ~MemoryEmptyException() throw();
};

class SyntaxException : public AbstractException
{
public:
  SyntaxException();
  ~SyntaxException() throw();
};

class BadInstException : public AbstractException
{
public:
  BadInstException();
  ~BadInstException() throw();
};

class OverFlowException : public AbstractException
{
public:
  OverFlowException();
  ~OverFlowException() throw();
};

class UnderFlowException : public AbstractException
{
public:
  UnderFlowException();
  ~UnderFlowException() throw();
};

#endif /* !EXCEPTION_HH_ */
