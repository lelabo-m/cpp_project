#ifndef FONCTOR_HH_
# define FONCTOR_HH_

template <typename T, typename P>
class Fonctor
{
public:
  Fonctor(T* obj, void (T::*func)(P))
  {
    _inst = obj;
    _func = func;
  }

  ~Fonctor()
  {
  }

  void	operator()(P data)
  {
    (_inst->*_func)(data);
  }

  T*	GetInst()
  {
    return _inst;
  }

  void	SetInst(T* newobj)
  {
    _inst = newobj;
  }

  void	SetFunc(void (T::*func)(P))
  {
    _func = func;
  }

private:
  T	*_inst;
  void	(T::*_func)(P);
};

#endif /* !FONCTOR_HH_ */

