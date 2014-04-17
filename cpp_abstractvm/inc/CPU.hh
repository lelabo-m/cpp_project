#ifndef CPU_HH_
# define CPU_HH_

#include "Instruction.hh"

#define NB_FUNC 11

class IChipset;

class ICPU
{
public:
  virtual void	Start() = 0;
  virtual void	selectAction(const Inst *) = 0;
  virtual void	LoadChipset(IChipset *) = 0;
  virtual ~ICPU() {};
};

class ICALC
{
public:
  virtual void		raiseException(const char *) = 0;
  virtual Inst*		getInst() = 0;
  virtual IOperand*	getData() = 0;
  virtual void		putData(IOperand *) = 0;
  virtual void		push(const Inst*) = 0;
  virtual void		pop(const Inst*) = 0;
  virtual void		dump(const Inst*) = 0;
  virtual void		print(const Inst*) = 0;
  virtual void		assert(const Inst*) = 0;
  virtual void		exit(const Inst*) = 0;
  virtual void		add(const Inst*) = 0;
  virtual void		sub(const Inst*) = 0;
  virtual void		mul(const Inst*) = 0;
  virtual void		div(const Inst*) = 0;
  virtual void		mod(const Inst*) = 0;
  virtual ~ICALC() {}
};

class CPU : public ICPU , protected ICALC
{
public:
  CPU();
  ~CPU();
  void		raiseException(const char *);
  Inst*		getInst();
  IOperand*	getData();
  void		putData(IOperand *);
  void		push(const Inst*);
  void		pop(const Inst*);
  void		dump(const Inst*);
  void		print(const Inst*);
  void		assert(const Inst*);
  void		exit(const Inst*);
  void		add(const Inst*);
  void		sub(const Inst*);
  void		mul(const Inst*);
  void		div(const Inst*);
  void		mod(const Inst*);
  void		Start();
  void		LoadChipset(IChipset *);
  void		selectAction(const Inst*);
private:
  IChipset	*_chipset;
  typedef void (CPU::*Action)(const Inst*);
  Action	funcTab[NB_FUNC];
};

#endif /* !CPU_HH_ */
