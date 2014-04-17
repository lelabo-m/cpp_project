#if defined(WIN32)
#include <windows.h>
#elif defined(__UNIX__)
#include <unistd.h>
#else
#endif

#include <iostream>
#include <fstream>

#include "MotherBoard.hh"
#include "Chipset.hh"

void __TEST_IO__()
{
  std::filebuf fb;

  std::istream inStream(&fb);
  std::ostream outStream(&fb);


  InputOutput *IO = new InputOutput(&std::cin, &outStream, true);
  std::cout << IO->Read() << std::endl;
}

void __TEST_CHIPSET_PARSING__(char *str)
{
  std::filebuf fb;

  std::istream inStream(&fb);
  std::ostream outStream(&fb);

  IInputOutput *IO = new InputOutput(&std::cin, &outStream, true);

  InstMemory *instmem = new InstMemory();
  DataMemory *datamem = new DataMemory();
  IRam *ram = new Ram(*instmem, *datamem);

  ICPU *cpu = new CPU();

  IChipset *chipset = new Chipset(*IO, *ram, *cpu);

  chipset->Forward(str, HardWare::RAM);
}

void __TEST_MOTHERBOARD__(int argc, char **argv)
{
  IMotherBoard *MB = new MotherBoard(argc, argv);
  MB->PowerOn();
  MB->PowerOff();
}


int main(int argc, char **argv)
{
  IMotherBoard *MB = new MotherBoard(argc, argv);
  MB->PowerOn();
  MB->PowerOff();
  return 0;
}
