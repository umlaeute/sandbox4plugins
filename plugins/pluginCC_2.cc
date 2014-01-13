#include <iostream>
#include "plugin.h"
#include "pluginfactory.hh"

class pluginCC_2 : public plugin {
public:
  std::string m_name;
  pluginCC_2(std::string s) : m_name(s) {
    MARK();
  }
  virtual ~pluginCC_2(void) {
	  MARK();
  }
  virtual bool open(const std::string s) {
	  MARK();
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
	  MARK();
    std::cout << "plugin(pluginC++2)::process '" << m_name << "':: " << id << std::endl;
  }
  void close(void) {
	  MARK();
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("pluginC++-2", pluginCC_2);
