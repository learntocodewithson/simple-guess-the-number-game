#ifndef GAME_H
#define GAME_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Base.h"
#include "Notice.h"
#include "View.h"

class Game: public Base, public Notice, public View {
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
  start(3);
 }

 void mediumLevel(){
  start(7);
 }

 void hardLevel(){
  start(15);
 }

 std::vector<int> generateRangeRandomNumbers(int limit){
  std::srand(std::time(nullptr));
  std::vector<int> randomNumbers;
  int counter = 1;

  do {
   int randomNumber = std::rand() % 100 + 1;
   bool duplicate = false;

   // checking if the random number already exists
   for(int i = 0; i < randomNumbers.size(); ++i){
    if(randomNumbers[i] == randomNumber){
     duplicate = true;
     break;
    }
   }

   if(!duplicate){
     randomNumbers.push_back(randomNumber);
     counter++;
   }
   
  } while(counter <= limit);

  return randomNumbers;
 }

 std::string displayRandomRangeNumbers(std::vector<int> randomNumbers){
  std::string randomNumbersDisplay;
 
  randomNumbersDisplay =  "[ ";

  for (int i = 0; i < randomNumbers.size(); ++i)
   randomNumbersDisplay += std::to_string(randomNumbers[i]) + " ";

  randomNumbersDisplay +=  "]";

  return randomNumbersDisplay;
 }

 void start(int limit){
  int user_guess, computer_chosen_number, random_index;
  std::vector<int> random_numbers = generateRangeRandomNumbers(limit);
  random_index = std::rand() % random_numbers.size();
  computer_chosen_number = random_numbers[random_index];

  std::cout << "\n\tEnter Your Guess Number from: " << ANSI_COLOR_GREEN << displayRandomRangeNumbers(random_numbers) << ANSI_COLOR_RESET << ": ";
  std::cin >> user_guess;

  if(user_guess == computer_chosen_number){
   std::cout << ANSI_COLOR_GREEN << "\n\tYou Win!" << ANSI_COLOR_RESET;
  }else{
   std::cout << ANSI_COLOR_RED << "\n\tComputer Wins!" << ANSI_COLOR_RESET;
  }
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