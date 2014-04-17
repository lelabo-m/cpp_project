#ifndef INSTRUCTION_HH_
# define INSTRUCTION_HH_

#include <string>
#include "Operand.hpp"

enum opcode {PUSH = 0, POP = 1, DUMP = 2, PRINT = 3, ASSERT = 4,
	     EXIT = 5, ADD = 6, SUB = 7, MUL = 8, DIV = 9, MOD = 10};

class Inst
{
private:
  const opcode		func;
  const std::string	value;
  const eOperandType	type;
public:
  Inst(const opcode, const std::string & = "", const eOperandType = None);
  Inst(const Inst &);
  ~Inst();
  opcode		getOpCode() const;
  eOperandType		getType() const;
  const std::string&	getValue() const;
};

#endif /* !INSTRUCTION_HH_ */
