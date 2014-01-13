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

  typedef pluginC_t (*pluginC_constructor_t)(const char*);
  typedef void      (*pluginC_destructor_t) (pluginC_t);
  typedef int       (*pluginC_open_t)       (pluginC_t, const char*);
  typedef void      (*pluginC_process_t)    (pluginC_t, int);
  typedef void      (*pluginC_close_t)      (pluginC_t);
  typedef struct pluginCallbacks_ {
    pluginC_constructor_t constructor;
    pluginC_destructor_t destructor;
    pluginC_open_t open;
    pluginC_process_t process;
    pluginC_close_t close;
  } pluginCallbacks_t;

  void register_plugin(const char*name, const pluginCallbacks_t*);

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus)
}

#ifndef _INCLUDE__PLUGIN_HH_
#define _INCLUDE__PLUGIN_HH_
class EXTERN plugin
{
 public:
  virtual ~plugin(void) {};

  virtual bool open(const std::string) = 0;
  virtual void process(int) = 0;
  virtual void close(void) = 0;

 public:
  //static inline plugin*constructor(const char*s) { return new plugin(s); }
  static inline void s_destructor(plugin*obj) {delete obj;}
  static inline  int s_open(plugin*obj, const char*s) {return obj->open(s);}
  static inline void s_process(plugin*obj, int i) {return obj->process(i);}
  static inline void s_close(plugin*obj) {return obj->close();}
};
#ifdef REGISTER_PLUGINFACTORY
# undef REGISTER_PLUGINFACTORY
#endif

namespace PluginFactoryRegistrar {
  template<class ChildClass, class BaseClass>
  class registrarC {
  private:
    static inline pluginC_t allocator(const char*s) {
	ChildClass*obj=new ChildClass(s);
	return (pluginC_t)obj;
    }
  public:
    registrarC(std::string ID) {
      pluginCallbacks_t cb;
      MARK();
      cb.constructor=(pluginC_constructor_t)allocator;
      cb.destructor =(pluginC_destructor_t )BaseClass::s_destructor;
      cb.open       =(pluginC_open_t       )BaseClass::s_open;
      cb.process    =(pluginC_process_t    )BaseClass::s_process;
      cb.close      =(pluginC_close_t      )BaseClass::s_close;
      register_plugin(ID.c_str(), &cb);
    }
  };
}
#define REGISTER_PLUGINFACTORY(id,TYP) \
   static PluginFactoryRegistrar::registrarC<TYP, plugin> fac_plugin_ ## TYP (id)
#endif /* _INCLUDE__PLUGIN_HH_ */
#endif /* c++ */

#endif	// for header file
