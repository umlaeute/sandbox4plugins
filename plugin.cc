#include "plugin.hh"
#include "pluginfactory.hh"
#include "exception.hh"

plugin :: ~plugin(void) {}
/* initialize the plugin factory */
static PluginFactoryRegistrar::dummy<plugin> fac_plugindummy;


#ifdef PLUGIN_META
class pluginMeta : public plugin {
private:
  std::vector<plugin*>m_handles; // all available handles
  plugin*m_handle; // currently opened handle (or NULL)
  std::vector<std::string>m_ids; // list of handle names

  // set to TRUE if we can use the current handle in another thread
  bool m_canThread;

  bool addPlugin( std::vector<std::string>available, std::string ID=std::string("")) {
    int count=0;

    std::vector<std::string>id;
    if(!ID.empty()) {
      // if requested 'cid' is in 'available' add it to the list of 'id's
      if(std::find(available.begin(), available.end(), ID)!=available.end()) {
	id.push_back(ID);
      } else {
	// request for an unavailable ID
	verbose(2, "backend '%s' unavailable", ID.c_str());
	return false;
      }
    } else {
      // no 'ID' given: add all available IDs
      id=available;
    }

    unsigned int i=0;
    for(i=0; i<id.size(); i++) {
      std::string key=id[i];
      verbose(2, "trying to add '%s' as backend", key.c_str());
      if(std::find(m_ids.begin(), m_ids.end(), key)==m_ids.end()) {
	// not yet added, do so now!
	plugin*handle=NULL;
	try {
	  handle=PluginFactory<plugin>::getInstance(key);
	} catch(MyException&x) {
	  handle=NULL;
	  verbose(1, "cannot use plugin plugin '%s': %s", key.c_str(), x.what());
	}
	if(NULL==handle)continue;
	m_ids.push_back(key);
	m_handles.push_back(handle);
	count++;
	verbose(2, "added backend#%d '%s'", m_handles.size()-1, key.c_str());
      }
    }
    return (count>0);
  }
public:
  pluginMeta(void) :
  m_handle(NULL),
  m_canThread(true)
  {
    gem::PluginFactory<plugin>::loadPlugins("plugin");
    std::vector<std::string>ids=gem::PluginFactory<plugin>::getIDs();

    if(!addPlugin(ids, "DirectShow"))
      addPlugin(ids, "AVI");

    addPlugin(ids, "gmerlin");
    addPlugin(ids, "QuickTime");
    addPlugin(ids, "quicktime4linux");
    addPlugin(ids, "MPEG3");
    addPlugin(ids, "aviplay");
    addPlugin(ids, "MPEG1");
    addPlugin(ids);

    unsigned int i;
    for(i=0; i<m_handles.size(); i++) {
      if(!m_handles[i]->isThreadable()) {
	m_canThread=false;
	break;
      }
    }
  }

  virtual ~pluginMeta(void) {
    unsigned int i;
    for(i=0; i<m_handles.size(); i++) {
      delete m_handles[i];
      m_handles[i]=NULL;
    }
  }

  virtual bool open(const std::string name, const gem::Properties&requestprops) {
    if(m_handle)close();

    std::vector<std::string> backends;
    if(requestprops.type("backends")!=gem::Properties::UNSET) {
      requestprops.get("backends", backends);
    }
    //      requestprops.erase("backends");

    bool tried=false;
    if(!backends.empty()) {
      unsigned int i, j;
      for(j=0; !m_handle && j<backends.size(); j++) {
	std::string id=backends[j];
	for(i=0; i<m_handles.size(); i++) {
	  if(id==m_ids[i] && (tried=true) && m_handles[i]->open(name, requestprops)) {
	    m_handle=m_handles[i];
	    break;
	  }
	}
      }
    }
    if(!tried) {
      if(!backends.empty() && !m_handles.empty()) {
	verbose(2, "no available backend selected, fall back to valid ones");
      }
      unsigned int i=0;
      for(i=0; i<m_handles.size(); i++) {
	if(m_handles[i] && m_handles[i]->open(name, requestprops)) {
	  m_handle=m_handles[i];
	  break;
	} else {

	}
      }
    }
    return (NULL!=m_handle);
  }

  virtual errCode changeImage(int imgNum, int trackNum=-1){
    if(m_handle)
      return m_handle->changeImage(imgNum, trackNum);

    return FAILURE;
  }

  virtual pixBlock* getFrame(void) {
    if(m_handle)
      return m_handle->getFrame();
    return NULL;
  }

  virtual void close(void)  {
    if(m_handle)
      m_handle->close();
    m_handle=NULL;
  }
};
#endif /* PLUGIN_META */

plugin*plugin::getInstance(void) {
  plugin*result=0;
#ifdef PLUGIN_META
  result=new pluginMeta();
#endif /* PLUGIN_META */
  return result;
}


void host_callback(int i) {
  std::cout << "HOSTcallback: "<<i<<std::endl;
}

#if 0
  typedef struct pluginCallbacks_ {
    bool(*open)(const char*);
    void(*process)(int);
    void(*close)(void);
  } pluginCallbacks_t;
#endif

static std::map<std::string, pluginCallbacks_t*>s_cbs;

class pluginC : public plugin {
  pluginC_t obj;
  pluginCallbacks_t*m_cb;
public:
  pluginC(std::string name) : m_cb(s_cbs[name]) {
    MARK();
    obj=m_cb->constructor(name.c_str());
  };
  virtual ~pluginC(void) {
    MARK();
    m_cb->destructor(obj);
  };
  virtual bool open(const std::string s) {
    MARK();
    return m_cb->open(obj, s.c_str());
  };
  virtual void process(int i) {
    MARK();
    return m_cb->process(obj, i);
  }
  virtual void close(void) {
    MARK();
    return m_cb->close(obj);
  }
};


void register_plugin(const char*name, const pluginCallbacks_t*cb0) {
  pluginCallbacks_t*cb=new pluginCallbacks_t;
  //memcpy(cb, cb0, sizeof(pluginCallbacks_t));
  *cb=*cb0;
  s_cbs[name]=cb;
  PluginFactoryRegistrar::registrar<pluginC, plugin>*registerC=new PluginFactoryRegistrar::registrar<pluginC, plugin>(name);
}
