#include <string>
#include <vector>
#include <iostream>

#include "dylib.hh"



void loadPlugins(std::vector<std::string>args) {
  for(unsigned int i=0; i<args.size(); i++) {
    std::string libname=args[i];
    std::cout << "library["<<i<<"] = " << libname << std::endl;
    try {
      Dylib dl(libname);
    } catch (MyException&e) {
      e.report();
    }
  }
}

std::vector<std::string>getCstringArray(int argc, char**argv) {
  std::vector<std::string>result;
  while(argc-->0) {
    result.push_back(*argv++);
  }
  return result;
}
void printStringVec(std::vector<std::string>args) {
  unsigned int i=0;
  for(i=0; i<args.size(); i++) {
    std::cout << "arg["<<i<<"] = " << args[i] << std::endl;
  }
}

extern "C" int main (int argc, char**argv);
int main(int argc, char**argv) {
  std::vector<std::string>args=getCstringArray(argc-1, argv+1);
  loadPlugins(args);
  return 0;
}
