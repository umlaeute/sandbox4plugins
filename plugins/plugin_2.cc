#include <iostream>
#include "plugin.h"
#include "pluginfactory.hh"

class plugin_2 : public plugin {
public:
  std::string m_name;
  plugin_2(std::string s) : m_name(s) {
    std::cout << "created plugin_2 plugin" << std::endl;
  }
  virtual ~plugin_2(void) {
    std::cout << "destroyed plugin_2 plugin" << std::endl;
  }
  bool open(std::string s) {
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
    std::cout << "plugin(plugin_2)::process '" << m_name << "':: " << id << std::endl;
  }
  void close(void) {
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("plugin_2", plugin_2);
