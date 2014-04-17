#ifndef CHIPSET_HH_
# define CHIPSET_HH_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <list>
#include "Operand.hpp"
#include "InputOutput.hh"
#include "Exception.hh"
#include "Instruction.hh"
#include "Ram.hh"
#include "CPU.hh"

namespace HardWare
{
  enum Composant { IO, CPU, RAM };
}

class IChipset
{
public:
  virtual ~IChipset() {};
  virtual void raiseException(const AbstractException&) const = 0;
  virtual void Forward(const std::string &, const HardWare::Composant) = 0;
  virtual void Forward(IOperand*, const HardWare::Composant) = 0;
  virtual IOperand *AskOperand() = 0;
  virtual Inst *AskInstruction() = 0;
  virtual void AskDump(Memory::Memtype) const = 0;
  virtual bool isExited() const = 0;
};

struct Instruction
{
  std::string name;
  size_t nb_param;
  opcode inst;
  Instruction(std::string _name, size_t _nb_param, opcode _inst)
    : name(_name), nb_param(_nb_param), inst(_inst) {}
};

enum NumberType {ENTIER, FLOTTANT, UNKNOWN};

struct Value
{
  std::string name;
  NumberType type;
  eOperandType opeType;
  Value(std::string _name, NumberType _type, eOperandType _opeType)
    : name(_name), type(_type), opeType(_opeType) {}
};

class Chipset : public IChipset
{
public:
  Chipset(IInputOutput &, IRam &, ICPU &);
  ~Chipset();
  virtual void Forward(const std::string &, const HardWare::Composant);
  virtual void Forward(IOperand*, const HardWare::Composant);
  virtual void raiseException(const AbstractException&) const;
  virtual IOperand *AskOperand();
  virtual Inst *AskInstruction();
  virtual void AskDump(Memory::Memtype) const;
  virtual bool isExited() const;

private:
  void sendToRamString(const std::string &);
  void parsingRules();
  eOperandType checkNumber(const std::string &);
  NumberType findNumberType(const std::string &);
  bool isDigit(const char) const;
  bool _isExited;

  std::vector<Instruction> _instVect;
  std::vector<Value> _valuesVect;

  IInputOutput &_io;
  IRam &_ram;
  ICPU &_cpu;
public:
  void Forward();
};

#endif
