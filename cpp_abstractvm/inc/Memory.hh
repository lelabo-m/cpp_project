#ifndef MEMORY_HH_
# define MEMORY_HH_

#include <iostream>
#include <queue>
#include <list>
#include "Operand.hpp"
#include "Instruction.hh"

namespace Memory
{
  enum Memtype {DATA, INST};
}

template <typename T>
class IMemory
{
public:
  virtual	~IMemory() {};
  virtual void	Push(T) = 0;
  virtual T	Pop() = 0;
  virtual void	Dump() const = 0;
};

class InstMemory : public IMemory<Inst *>
{
public:
  InstMemory();
  ~InstMemory();
  virtual void	Push(Inst *);
  virtual Inst*	Pop();
  virtual void	Dump() const;
private:
  std::list<Inst *>	_contain;
};

class DataMemory : public IMemory<IOperand *>
{
public:
  DataMemory();
  ~DataMemory();
  virtual void		Push(IOperand *);
  virtual IOperand*	Pop();
  virtual void		Dump() const;
private:
  std::list<IOperand *>	_contain;
};

#endif /* !MEMORY_HH_ */
