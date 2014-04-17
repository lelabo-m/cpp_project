#include <fstream>
#include "MotherBoard.hh"

MotherBoard::MotherBoard(int argc, char **argv)
{
	initIO(argc, argv);

	InstMemory *instmem = new InstMemory();
	DataMemory *datamem = new DataMemory();
	_ram = new Ram(*instmem, *datamem);
	_cpu = new CPU();

	_chipset = new Chipset(*_IO, *_ram, *_cpu);
	_cpu->LoadChipset(_chipset);
	_count = 1;
	_error = false;
}

void MotherBoard::initIO(int argc, char **argv)
{
	if (argc < 2)
	{
		_IO = new InputOutput(&std::cin, &std::cout, true);
		_file = false;
	}
	else
	{
		std::ifstream *inStream = new std::ifstream(argv[1]);
		if (!inStream->is_open())
		{
		  throw AbstractException("error open file");
		}
		_IO = new InputOutput(inStream, &std::cout, false);
		_file = true;
	}
}

MotherBoard::~MotherBoard()
{
}

void MotherBoard::PowerOn()
{
  std::string msg;

  while (_IO->isDone() == false)
    {
      msg = _IO->Read();
      try
	{
	  if (msg != "" && _chipset->isExited() == false)
	    _chipset->Forward(msg, HardWare::RAM);
	  ++_count;
	}
      catch (AbstractException&	e)
	{
	  std::stringstream ss;
          ss << "Error at line " << _count << " : " << e.what();
	  std::string   msg = ss.str();
          _chipset->Forward(msg, HardWare::IO);
	  _error = true;
	}
    }

  if (_chipset->isExited() == false)
    {
      std::stringstream ss;
      ss << "Program does not include an exit instruction.";
      std::string   msg = ss.str();
      _chipset->Forward(msg, HardWare::IO);
      return ;
    }

  if (!_error || !_file)
    _cpu->Start();
}

void MotherBoard::PowerOff()
{
  delete _chipset;
  delete _cpu;
  delete _ram;
  delete _IO;
}
