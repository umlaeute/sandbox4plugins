#include <iostream>
#include "plugin.hh"
#include "pluginfactory.hh"

class plugin_1 : public plugin {
public:
  std::string m_name;
  plugin_1(std::string s) : m_name(s) {
    std::cout << "created plugin_1 plugin" << std::endl;
  }
  virtual ~plugin_1(void) {
    std::cout << "destroyed plugin_1 plugin" << std::endl;
  }
  bool open(std::string s) {
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
    std::cout << "plugin(plugin_1)::process '" << m_name << "':: " << id << std::endl;
  }
  void close(void) {
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("plugin_1", plugin_1);
