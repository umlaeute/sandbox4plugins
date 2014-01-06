#ifndef _INCLUDE__PLUGINFACTORY_H_
#define _INCLUDE__PLUGINFACTORY_H_

#include "exportdef.hh"


#include <map>
#include <vector>
#include <string>

#include <typeinfo>
#include <iostream>

class EXTERN BasePluginFactory {
 protected:
  int doLoadPlugins(std::vector<std::string> files);
  BasePluginFactory(void);
  virtual ~BasePluginFactory(void);

  std::vector<std::string>get(void);
  void*get(std::string);
  void set(std::string, void*);

 private:
  class Pimpl;
  Pimpl*m_pimpl;
};

template<class Class>
class EXPORT PluginFactory : public BasePluginFactory {
 public:

  /**
   * constructor function type (without arguments)
   */
  typedef Class*(ctor_t)(void);

  /**
   * register a a constructor associated with a given ID
   */
  static void registerClass(std::string id, ctor_t*c);
  /**
   * get an instance of class constructed by the constructor associated with the given ID
   */
  static Class*getInstance(std::string id);

  /**
   * get a list of all IDs currently registered with this factory
   */
  static std::vector<std::string>getIDs(void);

  /**
   * load more plugins
   */
  static int loadPlugins(std::string basename, std::string path=std::string(""));

 private:
  static PluginFactory<Class>*s_factory;
 public:
  static PluginFactory<Class>*getPluginFactory(void);

 private:
  void doRegisterClass(std::string id, ctor_t*c);
  Class*doGetInstance(std::string id);
  std::vector<std::string>doGetIDs(void);
};


namespace PluginFactoryRegistrar {
  /**
   * creates a new ChildClass and returns it as a (pointer to) an instance of BaseClass
   */
  template<class ChildClass, class BaseClass>
  static BaseClass* allocator(void);

  /**
   * registers a ChildClass with a certain ID in the BaseClass factory
   *
   * example:
   *  static PluginFactoryRegistrar<Child, Base, std::string > basefac_childreg("childID"); // register Child as 'childID'
   *  Base*instance=PluginFactory<Base>::getInstance("childID"); // returns an instance of Child
   */
  template<class ChildClass, class BaseClass>
  struct registrar {
    registrar(std::string ID);
  };

  /**
   * registers a dummy constructor with a default ID
   */
  template<class BaseClass>
  struct dummy {
    dummy(void);
  };
};

/* include the actual implementation */
#include "pluginfactory_timple.hh"

#endif /* _INCLUDE__PLUGINFACTORY_H_ */
