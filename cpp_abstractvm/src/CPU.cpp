#include "MotherBoard.hh"

CPU::CPU()
{
  funcTab[PUSH] = &CPU::push;
  funcTab[POP] = &CPU::pop;
  funcTab[DUMP] = &CPU::dump;
  funcTab[PRINT] = &CPU::print;
  funcTab[ASSERT] = &CPU::assert;
  funcTab[EXIT] = &CPU::exit;
  funcTab[ADD] = &CPU::add;
  funcTab[SUB] = &CPU::sub;
  funcTab[MUL] = &CPU::mul;
  funcTab[DIV] = &CPU::div;
  funcTab[MOD] = &CPU::mod;
}

CPU::~CPU()
{
}

void          CPU::raiseException(const char *msg)
{
  throw AbstractException(msg);
}

Inst*		CPU::getInst()
{
  return _chipset->AskInstruction();
}

IOperand*	CPU::getData()
{
  return _chipset->AskOperand();
}

void		CPU::putData(IOperand* elem)
{
  _chipset->Forward(elem, HardWare::RAM);
}

void		CPU::push(const Inst* inst)
{
  FactoryOperand	facto;
  IOperand		*ope = NULL;

  if (inst->getType() != None)
     ope = facto.createOperand(inst->getType(), inst->getValue());
  _chipset->Forward(ope, HardWare::RAM);
}

void		CPU::pop(const Inst*)
{
  getData();
}

void		CPU::dump(const Inst*)
{
  _chipset->AskDump(Memory::DATA);
}

void		CPU::print(const Inst*)
{
  IOperand	*data = getData();
  if (data->getType() != Int8)
    throw AbstractException("Print fail!");
  Tint8		c(data->toString());
  std::stringstream	ss;
  std::string		msg;
  ss << c.getValue();
  ss >> msg;
  delete data;
  _chipset->Forward(msg, HardWare::IO);
}

void		CPU::assert(const Inst* inst)
{
  IOperand		*data = getData();
  push(inst);
  IOperand		*cmp = getData();
  if (cmp->getType() != data->getType() || cmp->toString() != data->toString())
    throw AbstractException("Assert fail!");
  putData(data);
  delete cmp;
}

void		CPU::exit(const Inst*)
{
  throw AbstractException("Exit");
}

void		CPU::add(const Inst*)
{
  IOperand&	nb1 = *getData();
  IOperand&	nb2 = *getData();
  IOperand*	nb3 = nb1 + nb2;
  putData(nb3);
}

void		CPU::sub(const Inst*)
{
  IOperand&	nb1 = *getData();
  IOperand&	nb2 = *getData();
  IOperand*	nb3 = nb1 - nb2;
  putData(nb3);
}

void		CPU::mul(const Inst*)
{
  IOperand&	nb1 = *getData();
  IOperand&	nb2 = *getData();
  IOperand*	nb3 = nb1 * nb2;
  putData(nb3);
}

void		CPU::div(const Inst*)
{
  IOperand&	nb1 = *getData();
  IOperand&	nb2 = *getData();
  IOperand*	nb3 = nb1 / nb2;
  putData(nb3);
}

void		CPU::mod(const Inst*)
{
  IOperand&	nb1 = *getData();
  IOperand&	nb2 = *getData();
  IOperand*	nb3 = nb1 % nb2;
  putData(nb3);
}

void		CPU::selectAction(const Inst* inst)
{
  (this->*funcTab[inst->getOpCode()])(inst);
}

void		CPU::LoadChipset(IChipset *chipset)
{
  _chipset = chipset;
}

void		CPU::Start()
{
  bool	exit = false;
  int	count = 0;

  while (exit == false)
    {
      try
	{
	  ++count;
	  Inst *inst = _chipset->AskInstruction();
	  if (inst->getOpCode() == EXIT)
	    {
	      exit = true;
	      continue;
	    }
	  selectAction(inst);
	  delete inst;
	}
      catch (AbstractException& e)
	{
	  std::stringstream ss;
	  ss << "Error at instruction  " << count << " : " << e.what();
	  std::string	msg = ss.str();
	  _chipset->Forward(msg, HardWare::IO);
	  exit = true;
	}
    }
}
