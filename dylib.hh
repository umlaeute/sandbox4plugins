/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

	- registers a loader with Pd

    Copyright (c) 2010-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef _INCLUDE__DYLIB_H_
#define _INCLUDE__DYLIB_H_

#include "exception.hh"
#include <string>
#include "exportdef.hh"

/* an opaque handle to the platform specific library handle */
class DylibHandle;

class EXTERN Dylib {
 private:
  DylibHandle*m_handle;

 public:
  Dylib(const std::string libname,
	const std::string extension=std::string("")
	) throw(MyException);

  Dylib(const Dylib&);

  virtual ~Dylib(void);

  typedef void (*function_t)(void);

  virtual Dylib& operator=(const Dylib&);

  // if void<procname>(void) exists in dylib, run it and return "true"
  // else return false;
  bool run(const std::string procname);

  // if <procname> exists in dylib, return it, else return NULL
  function_t proc(const std::string procname);

  public:
  /**
   * LoadLib(): convenience function that searches a library named <baselibname> and then runs <procname>()
   * if "extension" is NULL, a platform-specific default is used
   * on success "true" is returned, else "false
   */
  static bool LoadLib(const std::string procname,
		      const std::string baselibname,
		      const std::string fileext=std::string(""));


  static const std::string getDefaultExtension(void);
};




#endif
