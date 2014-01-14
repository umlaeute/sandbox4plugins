#include <iostream>
#include "plugin.hh"
#include "pluginfactory.hh"

class simple : public plugin {
public:
  std::string m_name;
  simple(void) : m_name("") {
	  MARK();
  }
  virtual ~simple(void) {
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
    std::cout << "plugin(simple)::process " << m_name << ":: " << id << std::endl;
  }
  void close(void) {
	  MARK();
    m_name="";
  }
};


REGISTER_PLUGINFACTORY("simple", simple);
