#ifndef SOUND_H_
#define SOUND_H_

#include <map>
#include <string>
#include "fmod_errors.h"
#include "wincompat.h"

class SoundException : public std::exception
{
 public:
  SoundException(const char *msg = "");
  virtual ~SoundException() throw();
  const char *  what() const throw();
 private:
  std::string   _msg;
};

class ISoundPlayer
{
 public:
  virtual ~ISoundPlayer() {};
  virtual void	InitSound(std::map<std::string, std::string>&) = 0;
  virtual void	PlaySound(const std::string&, int n = -1) = 0;
  virtual void	StopSound() = 0;
  virtual void	PauseSound() = 0;
};

class SoundPlayer : public ISoundPlayer
{
 public:
  SoundPlayer();
  ~SoundPlayer();
  void	InitSound(std::map<std::string, std::string>&);
  void	PlaySound(const std::string&, int n = -1);
  void	StopSound();
  void	PauseSound();
private:
  std::map<std::string, FMOD_SOUND *>	_sounds;
  FMOD_SYSTEM           *_system;
  FMOD_CHANNEL          *_channel;
};

#endif
