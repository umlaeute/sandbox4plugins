#include <string>
#include <vector>
#include <iostream>




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
  printStringVec(args);
  return 0;
}
