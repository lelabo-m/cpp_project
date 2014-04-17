#include "InputOutput.hh"

InputOutput::InputOutput(std::istream *inStream, std::ostream *outStream, bool readUser)
{
  _inStream = inStream;
  _outStream = outStream;
  _readUser = readUser;
  _done = false;
}


InputOutput::~InputOutput()
{
}

void InputOutput::Print(const std::string& str) const
{
  *_outStream << str << std::endl;
}

std::string InputOutput::Read()
{
  std::string line;

  if (!std::getline(*_inStream, line))
  {
    _done = true;
    return ("");
  }

  size_t pos = line.find(";;");
  if (pos != std::string::npos && _readUser == true)
    {
      _done = true;
      if (line.size() == 2)
		return ("");
      line.resize(pos);
    }
  else
  {
    pos = line.find(";");
    if (pos != line.npos)
      line.resize(pos);
  }
  return (line);
}

bool InputOutput::isDone() const
{
  return (_done);
}

bool InputOutput::isReadingUser() const
{
  return (_readUser);
}
