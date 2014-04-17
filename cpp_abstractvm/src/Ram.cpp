#include "Ram.hh"

Ram::Ram(InstMemory& inst, DataMemory& data) : _data(data), _inst(inst)
{
}

Ram::~Ram()
{
}

void		Ram::AskDump(Memory::Memtype type) const
{
  if (Memory::DATA == type)
    _data.Dump();
}

void		Ram::PutInst(Inst* elem)
{
  _inst.Push(elem);
}

void		Ram::PutData(IOperand* elem)
{
  _data.Push(elem);
}

Inst*		Ram::GetInst()
{
  return _inst.Pop();
}

IOperand*	Ram::GetData()
{
  return _data.Pop();
}
