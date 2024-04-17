#ifndef VIEW_H
#define VIEW_H
#include "Notice.h"
class View {

 protected:
 std::string title;
 
 public:
  std::string displayLine(){
   return "======================";
  }

  std::string displayTitle(){
   // "\n\t" to std::string("\n\t") is replaced to fix the issue about 
   // invalid operands to binary expression ('const char[3]' and 'const char[12]')
   return std::string("\n\t") + ANSI_COLOR_GREEN + displayLine() + "\n\t" + title + "\n\t" + displayLine() + "\n" + ANSI_COLOR_RESET;
  }
};
#endif