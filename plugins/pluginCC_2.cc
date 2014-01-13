#include <iostream>
#include "plugin.h"
#include "pluginfactory.hh"

class pluginCC_2 : public plugin {
public:
  std::string m_name;
  pluginCC_2(std::string s) : m_name(s) {
    std::cout << "created pluginC++2 plugin" << std::endl;
  }
  virtual ~pluginCC_2(void) {
    std::cout << "destroyed pluginC++2 plugin" << std::endl;
  }
  bool open(std::string s) {
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
    std::cout << "plugin(pluginC++2)::process '" << m_name << "':: " << id << std::endl;
  }
  void close(void) {
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("pluginC++-2", pluginCC_2);
