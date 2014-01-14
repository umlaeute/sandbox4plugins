#ifndef _INCLUDE__EXCEPTION_H_
#define _INCLUDE__EXCEPTION_H_

#include "exportdef.hh"
#include <string>

typedef struct _text t_object;

class EXTERN MyException
{
 public:
  MyException(void) throw();
  MyException(const char*error) throw();
  MyException(const std::string error) throw();
  virtual ~MyException(void) throw();

  virtual const char *what(void) const throw();
  virtual void report(const char*origin=0) const throw();
 private:
  const std::string ErrorString;
};

EXTERN void catchMyException(const char*name=NULL);


#endif /* _INCLUDE__EXCEPTION_H_ */
