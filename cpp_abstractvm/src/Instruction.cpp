#include "Instruction.hh"

Inst::Inst(const opcode code, const std::string& val, eOperandType _type) : func(code), value(val), type(_type)
{
}

Inst::Inst(const Inst &cpy) : func(cpy.func), value(cpy.value), type(cpy.type)
{

}

Inst::~Inst()
{
}

opcode	Inst::getOpCode() const
{
  return func;
}

const std::string&	Inst::getValue() const
{
  return value;
}

eOperandType	Inst::getType() const
{
  return type;
}
