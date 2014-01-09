#ifndef _INCLUDE__PLUGIN_H_
#define _INCLUDE__PLUGIN_H_

#include "exportdef.hh"

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus)
extern "C" {
#endif /* c++ */

  void host_callback(int);

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus)
  struct pluginCstruct_t;
#else
  struct pluginCstruct_ { } pluginCstruct_t;

#endif

  typedef void* pluginC_t;
  typedef struct pluginCallbacks_ {
    pluginC_t (*constructor)(void);
    void      (*destructor) (pluginC_t);
    int       (*open)       (pluginC_t, const char*);
    void      (*process)    (pluginC_t, int);
    void      (*close)      (pluginC_t);
  } pluginCallbacks_t;

  void register_plugin(const char*name, pluginCallbacks_t*);

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus)
}
#endif /* c++ */

#endif	// for header file
