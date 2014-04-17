#ifndef RAM_HH_
# define RAM_HH_

#include "Memory.hh"
#include "Instruction.hh"

class IRam
{
public:
  virtual void			PutInst(Inst*) = 0;
  virtual void			PutData(IOperand*) = 0;
  virtual Inst*			GetInst() = 0;
  virtual IOperand*		GetData() = 0;
  virtual void			AskDump(Memory::Memtype) const = 0;
  virtual ~IRam() {};
};

class Ram : public IRam
{
public:
  Ram(InstMemory&, DataMemory&);
  ~Ram();
  void			PutInst(Inst*);
  void			PutData(IOperand*);
  Inst*			GetInst();
  IOperand*		GetData();
  void			AskDump(Memory::Memtype) const;
private:
  DataMemory&	_data;
  InstMemory&	_inst;
};

#endif /* !RAM_HH_ */
