#include "plugin.h"
#include <stdio.h>

void plugin_setup(void) {
  static int i=0;
  printf("plugin_setup: %d\n", i);
  host_callback(i);
  i++;
}