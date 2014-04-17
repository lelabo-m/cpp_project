#include <sstream>
#include <limits>
#include <iostream>
#include "Operand.hpp"
#include "Exception.hh"

template <typename T>
std::string const&	AOperand<T>::toString() const
{
  return _value;
}

template <typename T>
eOperandType		AOperand<T>::getType() const
{
  return _type;
}

template <typename T>
int			AOperand<T>::getPrecision() const
{
  return getType();
}

template <typename T>
T			AOperand<T>::getValue() const
{
  std::stringstream	stream;
  T			val;

  stream << _value;
  stream >> val;
  return val;
}

template <>
char			AOperand<char>::getValue() const
{
  std::stringstream	stream;
  int			val;

  stream << _value;
  stream >> val;
  return val;
}

template <typename T>
T	convertString(const std::string& value)
{
  std::stringstream	stream;
  T			ret;

  stream << value;
  stream >> ret;
  return ret;
}

template <>
char	convertString<char>(const std::string& value)
{
  std::stringstream	stream;
  int			ret;

  stream << value;
  stream >> ret;
  return ret;
}

template <typename T>
IOperand*		AOperand<T>::operator+(const IOperand& other) const
{
  FactoryOperand	facto;
  eOperandType		rank;
  std::stringstream	stream;
  std::string		result;

  rank = (getType() > other.getType()) ? (getType()) : (other.getType());
  if (getType() != rank)
    {
      IOperand&	upcast = *facto.createOperand(rank, toString());
      return (upcast + other);
    }
  T	max, min;
  max = std::numeric_limits<T>::max();
  min = std::numeric_limits<T>::min();
  T	a, b;
  a = convertString<T>(toString());
  b = convertString<T>(other.toString());
  bool	samesign = ((a > 0 && b > 0) || (a < 0 && b < 0)) ? (true) : (false);
  bool	sign = (a > 0) ? (true) : (false);
  if (samesign)
    {
      if (sign && (max - a < b))
	throw OverFlowException();
      else if (!sign && (a < min - b))
	throw UnderFlowException();
    }
  stream.clear();
  stream << (a + b);
  stream >> result;
  return facto.createOperand(rank, result);
}

template <typename T>
IOperand*		AOperand<T>::operator-(const IOperand& other) const
{
  FactoryOperand	facto;
  eOperandType		rank;
  std::stringstream	stream;
  std::string		result;

  rank = (getType() > other.getType()) ? (getType()) : (other.getType());
  if (getType() != rank)
    {
      IOperand&	upcast = *facto.createOperand(rank, toString());
      return (upcast - other);
    }
  T	max, min;
  max = std::numeric_limits<T>::max();
  min = std::numeric_limits<T>::min();
  T	a, b;
  a = convertString<T>(toString());
  b = convertString<T>(other.toString());
  bool	samesign = ((a > 0 && b > 0) || (a < 0 && b < 0)) ? (true) : (false);
  bool	sign = (a > 0) ? (true) : (false);
  if (!samesign)
    {
      if (sign && (a > max + b))
	throw  OverFlowException();
      else if (!sign && (a < min + b))
	throw  UnderFlowException();
    }
  stream.clear();
  stream << (a - b);
  stream >> result;
  return facto.createOperand(rank, result);
}

template <typename T>
IOperand*		AOperand<T>::operator*(const IOperand& other) const
{
  FactoryOperand	facto;
  eOperandType		rank;
  std::stringstream	stream;
  std::string		result;

  rank = (getType() > other.getType()) ? (getType()) : (other.getType());
  if (getType() != rank)
    {
      IOperand&	upcast = *facto.createOperand(rank, toString());
      return (upcast * other);
    }
  T	max, min;
  max = std::numeric_limits<T>::max();
  min = std::numeric_limits<T>::min();
  T	a, b;
  a = convertString<T>(toString());
  b = convertString<T>(other.toString());
  bool	samesign = ((a > 0 && b > 0) || (a < 0 && b < 0)) ? (true) : (false);
  if (samesign && (a > max / b))
    throw  OverFlowException();
  else if (!samesign && (a < min / b))
    throw  UnderFlowException();
  stream.clear();
  stream << (a * b);
  stream >> result;
  return facto.createOperand(rank, result);
}

template <typename T>
IOperand*		AOperand<T>::operator/(const IOperand& other) const
{
  FactoryOperand	facto;
  eOperandType		rank;
  std::stringstream	stream;
  std::string		result;

  rank = (getType() > other.getType()) ? (getType()) : (other.getType());
  if (getType() != rank)
    {
      IOperand&	upcast = *facto.createOperand(rank, toString());
      return (upcast / other);
    }
  T	a, b, c;
  a = convertString<T>(toString());
  b = convertString<T>(other.toString());
  c = 0;
  if (b == c)
    throw  FloatingException();
  c = a / b;
  bool	samesign = ((a > 0 && b > 0) || (a < 0 && b < 0)) ? (true) : (false);
  bool	sign = (c > 0) ? (true) : (false);
  if (!samesign && sign)
    throw  OverFlowException();
  else if (!samesign && !sign)
    throw  UnderFlowException();
  stream.clear();
  stream << c;
  stream >> result;
  return facto.createOperand(rank, result);
}

template <typename T>
IOperand*		AOperand<T>::operator%(const IOperand& other) const
{
  FactoryOperand	facto;
  eOperandType		rank;
  std::stringstream	stream;
  std::string		result;

  rank = (getType() > other.getType()) ? (getType()) : (other.getType());
  if (getType() != rank)
    {
      IOperand&	upcast = *facto.createOperand(rank, toString());
      return (upcast % other);
    }
  T	a, b, c;
  a = convertString<T>(toString());
  b = convertString<T>(other.toString());
  c = 0;
  if (b == c)
    throw  FloatingException();
  c = ((int)a % (int)b);
  stream.clear();
  stream << c;
  stream >> result;
  return facto.createOperand(rank, result);
}

FactoryOperand::FactoryOperand()
{
  genTab[Int8] = &FactoryOperand::createInt8;
  genTab[Int16] = &FactoryOperand::createInt16;
  genTab[Int32] = &FactoryOperand::createInt32;
  genTab[Float] = &FactoryOperand::createFloat;
  genTab[Double] = &FactoryOperand::createDouble;
}

FactoryOperand::~FactoryOperand()
{
}

int		FactoryOperand::compareNumber(const std::string& num1,
					      const std::string& num2) const
{
  if (num1.size() != num2.size())
    return ((num1.size() > num2.size()) ? (1) : (-1));
  return num1.compare(num2);
}

template <typename T>
void		FactoryOperand::checkNumber(const std::string& value) const
{
  std::stringstream     ss;
  std::string		ref;

  ss << std::numeric_limits<T>::max();
  ss >> ref;
  if (compareNumber(value, ref) > 0)
    throw  OverFlowException();
  ss.clear();
  ss << std::numeric_limits<T>::min();
  ss >> ref;
  if (compareNumber(value, ref) > 0)
    throw  UnderFlowException();
}

template <>
void		FactoryOperand::checkNumber< char >(const std::string& value) const
{
  std::stringstream     ss;
  std::string		ref;

  ss << (int)std::numeric_limits<char>::max();
  ss >> ref;
  if (compareNumber(value, ref) > 0)
    throw  OverFlowException();
  ss.clear();
  ss << (int)std::numeric_limits<char>::min();
  ss >> ref;
  if (compareNumber(value, ref) > 0)
    throw  UnderFlowException();
}

IOperand*	FactoryOperand::createOperand(eOperandType type, const std::string& value)
{
  return (this->*genTab[type])(value);
}

IOperand*	FactoryOperand::createInt8(const std::string& value)
{
  checkNumber<char>(value);
  return new Tint8(value);
}

IOperand*	FactoryOperand::createInt16(const std::string& value)
{
  checkNumber<short int>(value);
  return new Tint16(value);
}

IOperand*	FactoryOperand::createInt32(const std::string& value)
{
  checkNumber<int>(value);
  return new Tint32(value);
}

IOperand*	FactoryOperand::createFloat(const std::string& value)
{
  checkNumber<float>(value);
  return new Tfloat(value);
}

IOperand*	FactoryOperand::createDouble(const std::string& value)
{
  checkNumber<double>(value);
  return new Tdouble(value);
}

Tint8::Tint8(const std::string& val)
{
  _type = Int8;
  _value = val;
}

Tint16::Tint16(const std::string& val)
{
  _type = Int16;
  _value = val;
}

Tint32::Tint32(const std::string& val)
{
  _type = Int32;
  _value = val;
}

Tfloat::Tfloat(const std::string& val)
{
  _type = Float;
  _value = val;
}

Tdouble::Tdouble(const std::string& val)
{
  _type = Double;
  _value = val;
}
