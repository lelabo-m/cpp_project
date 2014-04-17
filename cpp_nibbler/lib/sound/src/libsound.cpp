#include <iostream>
#include <exception>
#include <algorithm>
#include <stdlib.h>
#include "libsound.h"

SoundException::SoundException(const char *msg)
{
  _msg = msg;
}

SoundException::~SoundException() throw()
{
}

const char*     SoundException::what() const throw()
{
  return _msg.c_str();
}


int	Errcheck(FMOD_RESULT result)
{
  if (result != FMOD_OK)
    {
      std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result);
      return 1;
    }
  return 0;
}

SoundPlayer::SoundPlayer()
{
  _system = NULL;
  _channel = NULL;
}

SoundPlayer::~SoundPlayer()
{
  for (std::map<std::string, FMOD_SOUND*>::iterator it = _sounds.begin();
       it != _sounds.end(); ++it)
    FMOD_Sound_Release(it->second);
  FMOD_System_Close(_system);
  FMOD_System_Release(_system);
}

void	SoundPlayer::InitSound(std::map<std::string, std::string>& soundlist)
{
  FMOD_RESULT	res;

  res = FMOD_System_Create(&_system);
  if (Errcheck(res))
    throw SoundException("SoundPlayer Error : System create impossible");
  res = FMOD_System_Init(_system, 1, FMOD_INIT_NORMAL, NULL);
  if (Errcheck(res))
    throw SoundException("SoundPlayer Error : System initialisation impossible");
  for (std::map<std::string, std::string>::const_iterator it = soundlist.begin();
       it != soundlist.end(); ++it)
    {
      std::string	name;
      name = it->first;
      FMOD_SOUND	*sound = NULL;
      res = FMOD_System_CreateSound(_system, it->second.c_str(),
				    FMOD_SOFTWARE | FMOD_CREATESTREAM, 0, &sound);
      if (Errcheck(res))
	{
	  std::string err = "SoundPlayer Error : Can't load the file [" + it->second + "]";
	  throw SoundException(err.c_str());
	}
      _sounds[name] = sound;
    }
}

void	SoundPlayer::PlaySound(const std::string& name, int n)
{
  FMOD_RESULT	res;

  try
    {
      FMOD_Sound_SetLoopCount( _sounds[name], n);
      res = FMOD_System_PlaySound(_system, FMOD_CHANNEL_FREE, _sounds[name], 0, &(_channel));
    }
  catch (...)
    {
      throw SoundException("SoundPlayer Error : Unexpected error while playing music");
    }
  if (Errcheck(res))
    throw SoundException("SoundPlayer Error : Unexpected error while playing music");
}

void	SoundPlayer::StopSound()
{
  FMOD_RESULT	res;

  res = FMOD_Channel_Stop(_channel);
  if (Errcheck(res))
    throw SoundException("SoundPlayer Error : Unexpected error while stoping music");
}

void	SoundPlayer::PauseSound()
{
  FMOD_RESULT	res;
  FMOD_BOOL	state;

  FMOD_Channel_GetPaused(_channel, &state);

  if (state == 1)
    res = FMOD_Channel_SetPaused(_channel, 0);
  else
    res = FMOD_Channel_SetPaused(_channel, 1);
  if (Errcheck(res))
    throw SoundException("SoundPlayer Error : Unexpected error in pause manipulation");
}

extern "C"
{
  SoundPlayer*	entry_point()
  {
    return new SoundPlayer();
  }
}
