#ifndef GAME_H
#define GAME_H
#include "Notice.h"
#include "View.h"
class Game: public Notice, public View {
 int game_level;
 bool exit_game;

 public:
 Game(std::string t = ""){
  title = t;
  exit_game = false;
 }

 int main(){
  call();

  return 0;
 }

 void call(){
   system("clear");
   
   std::cout << displayTitle();
   std::cout << displayMenu();

   getUserInput();

   switch (game_level)
   {
   case 1:
    easyLevel(); // 3 range of numbers
    break;
   case 2:
    mediumLevel(); // 5 range of numbers
    break;
   case 3:
    hardLevel(); // 10 range of numbers
    break;
   default:
    exit_game = true;
    setSuccessNotice("\n\tThank you for using the game. Bye!");
    break;
   }

   if(hasNotice())
    std::cout << displayNotice();
   
 }

 void easyLevel(){
  std::cout << "Easy";
 }

 void mediumLevel(){
  std::cout << "Medium";
 }

 void hardLevel(){
  std::cout << "Hard";
 }

 std::string displayMenu(){
  // + concatenation is used to fix ANSI_COLOR_BLUE + std::string("\tMain Menu\n") 
  return ANSI_COLOR_CYAN + std::string("\tLevel of Difficulty\n") +
   "\t1. Easy\n"
   "\t2. Medium\n"
   "\t3. Hard\n"
   "\t4. Exit\n\n" + ANSI_COLOR_RESET;
 }

 void getUserInput(){
  std::cout << "\tSelect the level of difficulty: ";
  std::cin >> game_level;
 }
};
#endif