#ifndef _INCLUDE__PLUGIN_H_
#define _INCLUDE__PLUGIN_H_

#include "exportdef.hh"
#include <string>

class EXTERN plugin
{
 public:
  static plugin*getInstance(void);
  virtual ~plugin(void);

  virtual bool open(const std::string) = 0;
  virtual void process(int) = 0;
  virtual void close(void) = 0;
};

/**
 * \fn REGISTER_PLUGINFACTORY(const char *id, Class pluginClass)
 * registers a new class "pluginClass" with the plugin-factory
 *
 * \param id a symbolic (const char*) ID for the given class
 * \param pluginClass a class derived from "plugin"
 */
#define REGISTER_PLUGINFACTORY(id, TYP) static PluginFactoryRegistrar::registrar<TYP, plugin> fac_plugin_ ## TYP (id)

#endif	// for header file
