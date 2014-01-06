#include <iostream>
#include "plugin.hh"
#include "pluginfactory.hh"

class simple : public plugin {
public:
  std::string m_name;
  simple(void) : m_name("") {
    std::cout << "created simple plugin" << std::endl;
  }
  virtual ~simple(void) {
    std::cout << "destroyed simple plugin" << std::endl;
  }
  bool open(std::string s) {
    if(m_name.empty()) {
      m_name=s;
      return true;
    }
    return false;
  }
  void process(int id) {
    std::cout << "plugin(simple): " << m_name << ":: " << id << std::endl;
  }
  void close(void) {
    m_name="";
  }


};


REGISTER_PLUGINFACTORY("simple", simple);
