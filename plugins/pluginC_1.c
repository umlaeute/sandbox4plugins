#include "plugin.h"
#include <stdio.h>
#include <stdlib.h>

#define MARK() printf("%s[%d]: %s\n", __FILE__, __LINE__, __func__)

typedef struct pluginC1_ {
  int id;
  char*name;
} pluginC1_t;

pluginC_t plug_ctor(const char*s) {
  pluginC1_t*result=calloc(1, sizeof(pluginC1_t));
  static int id=666;
  result->id=id;
  id++;
  MARK();
  return(pluginC_t)result;
}
void plug_dtor(pluginC_t*p) { pluginC1_t*plug=(pluginC1_t*)p;
  MARK();
  free(plug->name); plug->name=NULL;
  free(plug);
}
int plug_open(pluginC_t*p, const char*s) { pluginC1_t*plug=(pluginC1_t*)p;
  MARK();
  if(!strcmp("fail", s))
    return 0;

  return 1;
}
void plug_close(pluginC_t*p) { pluginC1_t*plug=(pluginC1_t*)p;
  MARK();
}
void plug_process(pluginC_t*p, int i) { pluginC1_t*plug=(pluginC1_t*)p;
  MARK();
  printf("...processing[%s]: %d vs %d\n", plug->name, plug->id, i);
}

void plugin_setup(void) {
  pluginCallbacks_t cb;
  MARK();
  cb.constructor=plug_ctor;
  cb.destructor =plug_dtor;
  cb.open       =plug_open;
  cb.process    =plug_process;
  cb.close      =plug_close;
  register_plugin("pluginC1", &cb);
  register_plugin("pluginC1b", &cb);
}
