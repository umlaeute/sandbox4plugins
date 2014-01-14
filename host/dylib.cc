#ifdef _MSC_VER
# pragma warning( disable: 4091)
# define snprintf _snprintf
#endif /* _MSC_VER */

#include "dylib.hh"
//#include "Files.h"

#include <string>
#include <stdio.h>

#if defined __linux__ || defined __APPLE__ || defined __FreeBSD_kernel__
#include <unistd.h>
# define DL_OPEN
#endif

#ifdef DL_OPEN
# include <dlfcn.h>
#endif

#if defined _WIN32
# include <io.h>
# include <windows.h>
#endif

#include <iostream>

class DylibHandle {
public:
  std::string fullname;
#ifdef DL_OPEN
  void * dlhandle;
#endif
#ifdef _WIN32
  HINSTANCE w32handle;
#endif
  int dummy2;


  DylibHandle(void) :
  fullname(std::string()),
#ifdef DL_OPEN
  dlhandle(NULL),
#endif
#ifdef _WIN32
  w32handle(NULL),
#endif
  dummy2(0)
  {;}

  ~DylibHandle(void) {
    close();
  }

  static DylibHandle*open(const std::string filename) {
    DylibHandle*handle=new DylibHandle();

    if(filename.empty()) {
      throw(MyException(std::string("No DyLib name given!")));
    }

#ifdef DL_OPEN
    handle->dlhandle=dlopen(filename.c_str(), RTLD_NOW);
    if(handle->dlhandle) {
      handle->fullname=filename;
      return handle;
    }
#endif
#ifdef _WIN32
    UINT errorboxflags=SetErrorMode(SEM_FAILCRITICALERRORS);
    SetLastError(0);
    handle->w32handle=LoadLibrary(filename.c_str());
  DWORD errorNumber = GetLastError();
  errorboxflags=SetErrorMode(errorboxflags);
  if(handle->w32handle) {
    handle->fullname=filename;
    return handle;
  }
#endif

  delete handle;
  handle=NULL;

  std::string errormsg;
#ifdef DL_OPEN
  errormsg=dlerror();
  if(!errormsg.empty()) {
    std::string error="dlerror '";
    error+=errormsg;
    error+="'";
    throw(MyException(error));
  }
#endif
#ifdef _WIN32
  LPVOID lpErrorMessage=NULL;
  if(errorNumber) {
    FormatMessage(
                  FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL,
                  errorNumber,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR) &lpErrorMessage,
                  0, NULL );
  }
  std::cerr << "Dylib failed: #"<<errorNumber<<": ";
  if(lpErrorMessage) {
    std::cerr<<(const char*)lpErrorMessage;
  }else {
    std::cerr<<"(unknown)";
  }
  std::cerr<<std::endl;
  std::string error = "DLLerror(";
  char errbuf[10];
  snprintf(errbuf, 10, "0x%x", errorNumber);
  errbuf[10-1]=0;
  error+=errbuf;
  error+=")";
  if(lpErrorMessage) {
    error+=(const char*)lpErrorMessage;
  }
  std::cerr << "Dylib throwing: "<< error << std::endl;
  throw(MyException(std::string(error)));
#endif

  return NULL;
}

  static DylibHandle*open(const std::string filename, const std::string extension) {
    std::string fullname=filename+extension;
    if(fullname.empty()) {
      fullname=filename+DylibHandle::defaultExtension;
    }

    if(fullname.empty()) {
      std::string error="couldn't find '";
      error+=filename;
      error+="'.'";
      error+=extension;
      error+="'";
      throw(MyException(error));
    }

    return open(fullname);
  }

static const std::string defaultExtension;

void close(void) {
#ifdef DL_OPEN
  if(dlhandle)
    dlclose(dlhandle);
  dlhandle=NULL;
#endif
#ifdef _WIN32
  if(w32handle)
    FreeLibrary(w32handle);
  w32handle=NULL;
#endif
}

};

const std::string DylibHandle::defaultExtension =
#ifdef _WIN32
				    std::string(".dll")
#elif defined DL_OPEN
				    std::string(".so")
#else
				    std::string("")
#endif
				    ;
Dylib::Dylib(const std::string filename, const std::string extension) throw (MyException) : m_handle(0) {
  m_handle=DylibHandle::open(filename, extension);
  if(NULL==m_handle) {
    std::string err="unable to open '";
    err+=filename;
    if(!extension.empty()) {
      err+=".";
      err+=extension;
    }
    err+="'";
    throw MyException(err);
  }
}

Dylib::Dylib(const Dylib&org) : m_handle(NULL) {
  std::string filename=org.m_handle->fullname;
  m_handle=DylibHandle::open(filename);
  if(NULL==m_handle) {
    std::string err="unable to open '";
    err+=filename;
    err+="'";
    throw MyException(err);
  }
}

Dylib::~Dylib(void) {
  if(m_handle)
    delete m_handle;
  m_handle=NULL;
}

Dylib& Dylib::operator=(const Dylib&org) {
  if(m_handle)
    delete m_handle;
  m_handle=NULL;
  if(org.m_handle) {
    m_handle=DylibHandle::open(org.m_handle->fullname);
  }
  return *this;
}


Dylib::function_t Dylib::proc(const std::string procname) {
  function_t result=NULL;
  //  if(NULL==procname)return NULL;
#ifdef DL_OPEN
  dlerror();
  if(m_handle->dlhandle)
    result=(function_t)(dlsym(m_handle->dlhandle, procname.c_str()));
  if(NULL!=result)return result;
#endif
#ifdef _WIN32
  if(m_handle->w32handle)
    result=(function_t)(GetProcAddress(m_handle->w32handle, procname.c_str()));
  if(NULL!=result)return result;
#endif

  return result;
}

bool Dylib::run(const std::string procname) {
  function_t runproc=proc(procname);
  if(runproc) {
    (runproc)();
    return true;
  }
  return false;
}

bool Dylib::LoadLib(const std::string basefilename, const std::string extension, const std::string procname) {
  try {
    Dylib*dylib=new Dylib(basefilename, extension);
    if(NULL!=dylib) {
      dylib->run(procname);
      return true;
    }
  } catch (MyException&x) {
    std::cerr << "Dylib::LoadLib: "<<x.what()<<std::endl;
  }

  return false;
}


const std::string Dylib::getDefaultExtension(void) {
  return DylibHandle::defaultExtension;
}
