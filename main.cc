#include <string>
#include <vector>
#include <iostream>

#include "dylib.hh"
#include "pluginfactory.hh"
#include "plugin.hh"
extern "C" int main (int argc, char**argv);

std::vector<std::string>getCstringArray(int argc, char**argv) {
  std::vector<std::string>result;
  while(argc-->0) {
    result.push_back(*argv++);
  }
  return result;
}
void printStringVec(std::string id, std::vector<std::string>args) {
  unsigned int i=0;
  for(i=0; i<args.size(); i++) {
    std::cout << id << "["<<i<<"] = " << args[i] << std::endl;
  }
}

void loadPlugins(std::vector<std::string>args) {
  PluginFactory<plugin>::loadPlugins(args);
  std::vector<std::string>ids=PluginFactory<plugin>::getIDs();
  printStringVec("ID", ids);
}

int main(int argc, char**argv) {
  std::vector<std::string>args=getCstringArray(argc-1, argv+1);
  loadPlugins(args);
  return 0;
}
