#include "pluginfactory.hh"
#include "dylib.hh"
#include "sstream"

class BasePluginFactory::Pimpl {
  friend class BasePluginFactory;
  Pimpl(void) {
  }
  ~Pimpl(void) {
  }

  std::vector<std::string>p_loaded;
  std::map<std::string, void*>p_ctors;
};


BasePluginFactory::BasePluginFactory(void) : m_pimpl(new Pimpl) {
}
BasePluginFactory::~BasePluginFactory(void) {
  delete m_pimpl;  m_pimpl=NULL;
}

int BasePluginFactory::doLoadPlugins(std::vector<std::string>files) {
  int already=m_pimpl->p_loaded.size();
  int count=0;
  if(already>0) {
    std::cerr << "not reloading plugins (already loaded "<<already << ")" << std::endl;
    return 0;
  }
  unsigned int i;
  for(i=0; i<files.size(); i++) {
    Dylib*dll=NULL;
    const std::string f=files[i];
    // check whether this file has already been loaded
    // LATER make checks more sophisticated (like checking file-handles)
    bool alreadyloaded=false;
    unsigned int j;
    for(j=0; j<m_pimpl->p_loaded.size(); j++)
      if(f == m_pimpl->p_loaded[j]) {
	alreadyloaded=true;
	std::cerr << "not reloading '"<<f<<"'"<<std::endl;
	break;
      }
    if(alreadyloaded)continue;

    std::cerr << "dylib loading file '" << f << "'!" << std::endl;
    dll=NULL;
    try {
      dll=new Dylib(f, "");
    } catch (MyException&x) {
      std::cerr << "library loading returned: " << x.what() << std::endl;
      dll=NULL;
    }
    if(dll){ // loading succeeded
        try {
            m_pimpl->p_loaded.push_back(f);
            count++;
        } catch (MyException&x) {
            std::cerr << "plugin loading returned: " << x.what() << std::endl;
        }
    }

  }

  return count;
}

std::vector<std::string>BasePluginFactory::get() {
  std::vector<std::string>result;
  if(m_pimpl) {
    std::map<std::string, void*>::iterator iter = m_pimpl->p_ctors.begin();
    for(; iter != m_pimpl->p_ctors.end(); ++iter) {
      if(NULL!=iter->second)
        result.push_back(iter->first);
    }
  }
  return result;
}

void*BasePluginFactory::get(std::string id) {
  void*ctor=NULL;
  if(m_pimpl)
    ctor=m_pimpl->p_ctors[id];
  return ctor;
}

void BasePluginFactory::set(std::string id, void*ptr) {
  if(m_pimpl)
    m_pimpl->p_ctors[id]=ptr;
}
