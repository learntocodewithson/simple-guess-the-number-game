#ifndef GAME_H
#define GAME_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Base.h"
#include "Notice.h"
#include "View.h"

class Game: public Base, public Notice, public View {
 int game_level, user_win_count, computer_win_count, round_counter;
 bool exit_game;

 public:
 Game(std::string t = ""){
  title = t;
  exit_game = false;
  user_win_count = computer_win_count = round_counter= 0;
  
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

 void startNow(int limit, int win_limit, std::string level){
  std::cout << ANSI_COLOR_BLUE << "\n\tYou choose " << level << " level. Whoever got " << win_limit << " wins first, will be the winner." << std::endl << ANSI_COLOR_RESET;
  do {
   round_counter++;
   startTheGame(limit);
  } while(user_win_count != win_limit && computer_win_count != win_limit);

  if(user_win_count == win_limit){
    setSuccessNotice("\n\tCongratulations, You Win!");
  }else {
    setErrorNotice("\n\tComputer Wins!, Better luck next time! :)");
  }
 }

 void easyLevel(){
  startNow(3, 3, "easy");
 }

 void mediumLevel(){
  startNow(7, 5, "medium");
 }

 void hardLevel(){
  startNow(10, 7, "hard");
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

 void startTheGame(int limit){
  int user_guess, computer_chosen_number, random_index;
  std::vector<int> random_numbers = generateRangeRandomNumbers(limit);
  random_index = std::rand() % random_numbers.size();
  computer_chosen_number = random_numbers[random_index];

  std::cout << ANSI_COLOR_ORANGE << "\n\tRound " << round_counter << ANSI_COLOR_RESET;
  std::cout << "\n\tEnter Your Guess Number from: " << ANSI_COLOR_GREEN << displayRandomRangeNumbers(random_numbers) << ANSI_COLOR_RESET << ": ";
  std::cin >> user_guess;

  if(user_guess == computer_chosen_number){
   user_win_count++;
  //  std::cout << ANSI_COLOR_GREEN << "\n\tYou Win!" << ANSI_COLOR_RESET;
  }else{
   computer_win_count++;
  //  std::cout << ANSI_COLOR_RED << "\n\tComputer Wins!" << ANSI_COLOR_RESET;
  }

  std::cout << ANSI_COLOR_GREEN << "\n\tUser Win: " << user_win_count << ANSI_COLOR_RESET;
  std::cout << ANSI_COLOR_RED << "\n\tComputer Win: " << computer_win_count << std::endl << ANSI_COLOR_RESET;
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