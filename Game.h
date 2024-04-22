#ifndef GAME_H
#define GAME_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include<sstream>
#include<fstream>
#include "Base.h"
#include "Notice.h"
#include "View.h"

struct KeyValuePair {
  std::string key;
  std::string value;
};

class Game: public Base, public Notice, public View {
 int game_level, user_win_count, computer_win_count, round_counter;
 bool exit_game;
 std::vector<KeyValuePair> ENV;

 public:
 Game(std::string t = ""){
  title = t;
  exit_game = false;
  user_win_count = computer_win_count = round_counter= 0;
  loadEnv();
 }

 int main(){
  call();

  return 0;
 }

 void call(){
   do {
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
    case 4:
      settings();
      break;
    case 5:
      exit_game = true;
      setSuccessNotice("\n\tThank you for using the game. Bye!");
      break;
    default:
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      setErrorNotice("\n\tInvalid Input.");
      break;
    }

    if(hasNotice()){
      std::cout << displayNotice();
      resetNotice();
    }
      

   } while(!exit_game);
 }

 void loadEnv(){
  std::string row_data, tmp_key, tmp_value;

  std::ifstream Settings(".env");

  if(Settings.is_open()){
    while(getline(Settings, row_data)){
      std::istringstream scanner(row_data);
      getline(scanner, tmp_key, ':');
      getline(scanner, tmp_value);

      envInsert(tmp_key, tmp_value);
    }
  }

  Settings.close();
 }

 void envInsert(std::string tmp_key, std::string tmp_value){
  KeyValuePair pair;

  removeExtraSpaces(tmp_value);
  
  pair.key = tmp_key;
  pair.value = tmp_value;

  ENV.push_back(pair);
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
    setErrorNotice("\n\n\n\tComputer Wins!, Better luck next time! :)");
  }

  resetUserComputerWinningScores();
 }

 void resetUserComputerWinningScores(){
  user_win_count = computer_win_count = round_counter= 0;
 }

 void easyLevel(){
  startNow(
    stoi(searchValue("range_number_limit_easy_level")), 
    stoi(searchValue("winning_limit_easy_level")), 
    "easy"
  );
 }

 void mediumLevel(){
  startNow(
    stoi(searchValue("range_number_limit_medium_level")), 
    stoi(searchValue("winning_limit_medium_level")), 
    "medium"
  );
 }

 void hardLevel(){
  startNow(
    stoi(searchValue("range_number_limit_hard_level")), 
    stoi(searchValue("winning_limit_hard_level")), 
    "hard"
  );
 }

 void settings(){
  std::string edit_answer;
  std::cout << "\n\tSettings" << std::endl;

  // display settings variables
  displaySettingsVariables();

  std::cout << "\n\tWould you like to edit? <y or n>: ";
  std::cin >> edit_answer;
  
  if(edit_answer == "y"){
   updateSettingsVariables();
  }
 }

 void updateSettingsVariables(){
  std::string row_data, tmp_key, tmp_value, setting_value, setting_key, update_setting;
  std::vector<std::string> updatedSettings;
  std::ifstream Settings(".env");

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if(Settings.is_open()){
    while(getline(Settings, row_data)){
      std::istringstream scanner(row_data);
      getline(scanner, tmp_key, ':');
      getline(scanner, tmp_value);

      setting_key = tmp_key;
      setting_value = "";

      replaceChar(setting_key, '_', ' ');
      toUpperCase(setting_key);
      removeExtraSpaces(tmp_value);

      std::cout << "\n\t" << setting_key << "[" << tmp_value << "]: ";
      getline(std::cin, setting_value);

      if(setting_value != "")
        tmp_value = setting_value;

      update_setting = tmp_key + ": " + tmp_value;

      updatedSettings.push_back(update_setting);
    }
  }else{
    setErrorNotice("\nUnable to open the .env file");
  }

  Settings.close();

  // create a new file and load the new list on .env
  std::ofstream WriteSettings(".env");

  if(WriteSettings.is_open()){
    for(size_t i = 0; i < updatedSettings.size(); i++){
      if(updatedSettings[i] != "")
        WriteSettings << updatedSettings[i] << "\n";
    }

    WriteSettings.close();

    // Clear the vector to reset it
    ENV.clear();

    loadEnv();
  }else {
    setErrorNotice("\nUnable to create and open .env file");
  }
 }

 void displaySettingsVariables(){
   std::string tmp_key;
   for(size_t i = 0; i < ENV.size(); i++){
    tmp_key = ENV[i].key;

    replaceChar(tmp_key, '_', ' ');
    toUpperCase(tmp_key);
    
    std::cout << "\t" << tmp_key << ": " << ENV[i].value << std::endl; 
   }
 }

 void getUserInput(){
  std::cout << "\tSelect the level of difficulty: ";
  std::cin >> game_level;
 }

 void startTheGame(int limit){
  int user_guess, computer_chosen_number, random_index;
  bool validGuessNumber = false;
  std::vector<int> random_numbers = generateRangeRandomNumbers(limit);
  random_index = std::rand() % random_numbers.size();
  computer_chosen_number = random_numbers[random_index];

  std::cout << ANSI_COLOR_ORANGE << "\n\tRound " << round_counter << ANSI_COLOR_RESET;
 
  do {

    if(hasNotice())
      std::cout << displayNotice();

    std::cout << "\n\tEnter Your Guess Number from: " << ANSI_COLOR_GREEN << displayRandomRangeNumbers(random_numbers) << ANSI_COLOR_RESET << ": ";
    if (!(std::cin >> user_guess)) {
      resetUserScanInput("\n\tInvalid Guess Number");
    } else {
      if(!validateIfOutOfRange(random_numbers, user_guess)){
        resetNotice();

        validGuessNumber = true;

        if(user_guess == computer_chosen_number){
          user_win_count++;
        }else{
          computer_win_count++;
        }

        std::cout << ANSI_COLOR_GREEN << "\n\tUser Win: " << user_win_count << ANSI_COLOR_RESET;
        std::cout << ANSI_COLOR_RED << "\n\tComputer Win: " << computer_win_count << std::endl << ANSI_COLOR_RESET;
      }else{
        resetUserScanInput("\n\tOut of Range Guess Number.");
      }
    }
  } while(!validGuessNumber);
 }

 void resetUserScanInput(std::string error_message){
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  setErrorNotice(error_message);
 }

 std::string searchValue(std::string tmp_key){
  for(size_t i = 0; i < ENV.size(); i++){
   if(ENV[i].key == tmp_key)
    return ENV[i].value; 
  }
  return "";
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

 bool validateIfOutOfRange(std::vector<int> randomNumbers, int user_input){
  for (int i = 0; i < randomNumbers.size(); ++i){
    if(randomNumbers[i] == user_input)
     return false;
  }
  
  return true;
 }

 std::string displayMenu(){
  // + concatenation is used to fix ANSI_COLOR_BLUE + std::string("\tMain Menu\n") 
  return ANSI_COLOR_CYAN + std::string("\tLevel of Difficulty\n") +
   "\t1. Easy\n"
   "\t2. Medium\n"
   "\t3. Hard\n"
   "\t4. Settings\n"
   "\t5. Exit\n\n" + ANSI_COLOR_RESET;
 }
};
#endif