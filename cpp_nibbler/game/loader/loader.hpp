#ifndef LOADER_H_
# define LOADER_H_

#include <iostream>
#include <string>
#include <exception>
#include <dlfcn.h>

class DLLoadingException : public std::exception
{
 public:
  DLLoadingException(const char *msg = "");
  virtual ~DLLoadingException() throw();
  const char *  what() const throw();
 private:
  std::string   _msg;
};

template <typename T>
class DLLoader
{
public:
  DLLoader(const std::string& lib)
  {
    char	*error;

    _lib = lib;
    _handle = dlopen(lib.c_str(), RTLD_LAZY);
    if (!_handle)
      {
	error = dlerror();
	if (error)
	  throw DLLoadingException(error);
	else
	  throw DLLoadingException();
      }
  }

  ~DLLoader()
  {
    std::string   msg("Error : Faillure when we close the librairy plugin [");

    msg = msg + _lib + "]";
    if (dlclose(_handle))
      throw DLLoadingException(msg.c_str());
  }

  T*	LoadObject(const std::string& func)
  {
    T*    (*external_creator)();
    char  *error;

    external_creator = reinterpret_cast<T* (*)()>(dlsym(_handle, func.c_str()));
    if (!external_creator)
      {
	error = dlerror();
	if (error)
	  throw DLLoadingException(error);
	else
	  throw DLLoadingException();
      }
    return (external_creator());
  }

private:
  void		*_handle;
  std::string	_lib;
};

#endif /* !LOADER_H_ */
