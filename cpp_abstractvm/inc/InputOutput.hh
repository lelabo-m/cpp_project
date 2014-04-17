#ifndef INPUTOUTPUT_HH_
# define INPUTOUTPUT_HH_

#include <string>
#include <iostream>

class IInputOutput
{
public:
  virtual void Print(const std::string&) const = 0;
  virtual std::string Read() = 0;
  virtual bool isReadingUser() const = 0;
  virtual bool isDone() const = 0;
  virtual ~IInputOutput() {};
};

class InputOutput : public IInputOutput
{
public:
  InputOutput(std::istream *inStream, std::ostream *outStream, bool);
  ~InputOutput();
  virtual void Print(const std::string&) const;
  virtual std::string Read();
  virtual bool isReadingUser() const;
  virtual bool isDone() const;
private:
  bool _done;
  bool _readUser;
  std::istream *_inStream;
  std::ostream *_outStream;
};

#endif
