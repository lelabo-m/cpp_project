#ifndef MOTHERBOARD_HH_
# define MOTHERBOARD_HH_

#include <iostream>
#include <fstream>
#include "CPU.hh"
#include "Chipset.hh"

class IMotherBoard
{
public:
  virtual void PowerOn() = 0;
  virtual void PowerOff() = 0;
};

class MotherBoard : public IMotherBoard
{
public:
  MotherBoard(int, char**);
  ~MotherBoard();
  virtual void PowerOn();
  virtual void PowerOff();

private:
  void initIO(int, char**);
  IInputOutput *_IO;
  IChipset *_chipset;
  IRam *_ram;
  ICPU *_cpu;
  int	_count;
  bool	_error;
  bool	_file;
};

#endif
