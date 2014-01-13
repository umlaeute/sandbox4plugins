#include <iostream>
#include "plugin.hh"
#include "pluginfactory.hh"

class pluginCC_1 : public plugin {
public:
  std::string m_name;
  pluginCC_1(std::string s) : m_name(s) {
    std::cout << "created plugin++_1 plugin" << std::endl;
  }
  virtual ~pluginCC_1(void) {
    std::cout << "destroyed plugin++_1 plugin" << std::endl;
  }
  bool open(std::string s) {
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
    std::cout << "plugin(plugin++_1)::process '" << m_name << "':: " << id << std::endl;
  }
  void close(void) {
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("pluginC++_1", pluginCC_1);
