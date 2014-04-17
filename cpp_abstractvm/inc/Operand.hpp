#ifndef OPERAND_HH_
# define OPERAND_HH_

#include <string>

#define NB_TYPE 5

enum eOperandType { Int8 = 0, Int16 = 1, Int32 = 2, Float = 3, Double = 4, None = 5 };

class IOperand
{
public:
  virtual std::string const&	toString() const = 0;
  virtual int			getPrecision() const = 0;
  virtual eOperandType		getType() const = 0;
  virtual IOperand*		operator+(const IOperand &) const = 0;
  virtual IOperand*		operator-(const IOperand &) const = 0;
  virtual IOperand*		operator*(const IOperand &) const = 0;
  virtual IOperand*		operator/(const IOperand &) const = 0;
  virtual IOperand*		operator%(const IOperand &) const = 0;
  virtual ~IOperand() {}
};

template <typename T>
class AOperand : public IOperand
{
public:
  virtual T			getValue() const;
  virtual std::string const&	toString() const;
  virtual int			getPrecision() const;
  virtual eOperandType		getType() const;
  virtual IOperand*		operator+(const IOperand &) const;
  virtual IOperand*		operator-(const IOperand &) const;
  virtual IOperand*		operator*(const IOperand &) const;
  virtual IOperand*		operator/(const IOperand &) const;
  virtual IOperand*		operator%(const IOperand &) const;
  virtual			~AOperand() {}
protected:
  std::string	_value;
  eOperandType	_type;
};

class FactoryOperand
{
public:
  FactoryOperand();
  ~FactoryOperand();
  IOperand*		createOperand(eOperandType, const std::string &);
private:
  template <typename T>
  void			checkNumber(const std::string&) const;
  int			compareNumber(const std::string&, const std::string&) const;
  IOperand*		createInt8(const std::string &);
  IOperand*		createInt16(const std::string &);
  IOperand*		createInt32(const std::string &);
  IOperand*		createFloat(const std::string &);
  IOperand*		createDouble(const std::string &);
private:
  typedef IOperand* (FactoryOperand::*CreateFunc)(const std::string&);
  CreateFunc		genTab[NB_TYPE];
};

class Tint8 : public AOperand<char>
{
public:
  Tint8(const std::string& val = "0");
  ~Tint8() {};
};

class Tint16 : public AOperand<short int>
{
public:
  Tint16(const std::string& val = "0");
  ~Tint16() {};
};

class Tint32 : public AOperand<int>
{
public:
  Tint32(const std::string& val = "0");
  ~Tint32() {};
};

class Tfloat : public AOperand<float>
{
public:
  Tfloat(const std::string& val = "0.f");
  ~Tfloat() {};
};

class Tdouble : public AOperand<double>
{
public:
  Tdouble(const std::string& val = "0.f");
  ~Tdouble() {};
};

#endif /* !OPERAND_HH_ */
