#include <iostream>
#include "plugin.hh"
#include "pluginfactory.hh"

class pluginCC_1 : public plugin {
public:
  std::string m_name;
  pluginCC_1(std::string s) : m_name(s) {
	  MARK();
  }
  virtual ~pluginCC_1(void) {
	  MARK();
  }
  bool open(const std::string s) {
	  MARK();
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
	  MARK();
    std::cout << "plugin(plugin++_1)::process '" << m_name << "':: " << id << std::endl;
  }
  void close(void) {
	  MARK();
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("pluginC++_1", pluginCC_1);
