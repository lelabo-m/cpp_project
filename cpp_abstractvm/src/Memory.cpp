#include <algorithm>
#include "Exception.hh"
#include "Memory.hh"

InstMemory::InstMemory()
{
}

InstMemory::~InstMemory()
{
}

void		InstMemory::Push(Inst* inst)
{
  _contain.push_back(inst);
}

Inst*		InstMemory::Pop()
{
  if (_contain.size() <= 0)
    throw MemoryEmptyException();
  Inst	*elem = _contain.front();
  _contain.pop_front();
  return elem;
}

void		InstMemory::Dump() const
{
}

DataMemory::DataMemory()
{
}

DataMemory::~DataMemory()
{
}

void		DataMemory::Push(IOperand *data)
{
  _contain.push_front(data);
}

IOperand*	DataMemory::Pop()
{
  if (_contain.size() <= 0)
    throw MemoryEmptyException();
 IOperand	*elem = _contain.front();
 _contain.pop_front();
 return elem;
}

void		DumpFunc(IOperand *op)
{
  std::cout << op->toString() << std::endl;
}

void		DataMemory::Dump() const
{
  std::for_each(_contain.begin(), _contain.end(), DumpFunc);
}
