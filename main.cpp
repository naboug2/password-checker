/****************************
Program 3: Password Checker
Course: CS 141, Fall 2022
System: MacOS using VSCode
Starter Code Author: Dr. Sara Riazi
Student Author: Nuha Abougoash 
 **************************/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";

// this functions checks rule 1 to see if the selected password is at least 8 characters long
bool rule1(string password){
   if (password.size() >= 8){ 
      return true;
   } 
   return false; 
}

// this function checks rule 2 to see if the selected password has at least one upper case letter
bool rule2(string password){
   // loop through each character of the password
   for (int i=0; i < password.size(); i++){
      // return true if there is an upper case letter and false otherwise
      if (isupper(password[i])){
         return true;
      }
   }
   return false;
}

// this function checks rule 3 to see if the selected password has at least one lower case letter
bool rule3(string password){
   // loop through each character of the password
   for (int i=0; i < password.size(); i++){
      // return true if there is an lower case letter and false otherwise
      if (islower(password[i])){
         return true;
      }
   }
   return false;
}

//this function checks rule 4 to see if the selected password has at least one digit
bool rule4(string password){
   // loop through each character of the password
   for (int i=0; i < password.size(); i++){
      // return true if there is a digit and false otherwise
      if (isdigit(password[i])){
         return true;
      }
   }
   return false;
}

//this function checks rule 5 to see if password has at least one special character @, !, #, ^, &, *, or $
bool rule5(string password){
   // loop through each character of the password
   for (int i=0; i < password.size(); i++){
      // return true if there is a speacial character and false otherwise
      if (( password[i] == '@' ) || (password[i] == '!') || (password[i] == '#') || (password[i] == '^') || (password[i] == '&') || (password[i] == '*') || (password[i] == '$')) {
         return true;
      }
   }
   return false;
}

//this function creates a new password with all lower case letters, without any special characters
string removeSpecialCharacter(string password) {
   string newPass; //declare variable
   //loop through each letter in password
   for (int i = 0; i < password.size(); i++) {
      if (isalnum(password[i])) { //check if aplphanumeric at each index
          //push each index into new password variable and change all letters to lower case
         newPass.push_back(tolower(password[i]));  
      }
   }
   return newPass; //return updated password
}

//this function completes binary search
bool binarySearch(vector<string> leakedPass, string password) {
   int low = 0, high = leakedPass.size() - 1; 
   int mid;
   password = removeSpecialCharacter(password); //call function to remove all special characters in password
   while (low <= high) {
      mid = (low + high) / 2;  
      //this new password takes the leaked password with no special characters and compares it to inputed password
      int newPass = password.compare(removeSpecialCharacter(leakedPass.at(mid))); 
      //check if new password found in mid the return true 
      if (newPass == 0){  
         return true; 
      }
      else if (newPass > 0){ //otherwise if its smaller than mid then check the left hand side of vector
         low = mid + 1;
      }
      else{
         high = mid - 1; // if its bigger than mid then check the right hand side of vector
      }
   }
   return false;
}

//this function checks if selected password has been leaked
bool rule6(string password) {
   vector<string> leakedpass; //declare vector to store all data in file
   string temp;  //decalre temporary variable
   ifstream leaked_password_file; 
   leaked_password_file.open("alleged-gmail-passwords.txt");   //open file
   if (leaked_password_file.is_open()) {
      while (leaked_password_file >> temp) {
         leakedpass.push_back(temp);  //push each line in file into vector
      }
      leaked_password_file.close();  //close file
   }
   return binarySearch(leakedpass, password); //call binary search function to check if password has been leaked
}

//this function check if selected password is contained in word file
bool rule7(string password){
   vector<string> word; //declare vector to store all data in file
   ifstream english_word_file;
   english_word_file.open("words_5.txt");  //open file
   string temp; //declare temparary variable
   if (english_word_file.is_open()) { 
      while (english_word_file >> temp) {
         word.push_back(temp); //push all words in file into vector
      }
      english_word_file.close();  //close file
   } 
   password = removeSpecialCharacter(password); //call function to remove all special characters
    //loop through each letter in word
   for (int i = 0; i < word.size(); i++) {
      //check if at letter at any index of word is found in the password
      if (password.find(word[i]) != std::string::npos) { 
         return false; //password rejected because it is found inside of file
      }
   }
   return true; 
}

/****
 * Runs the main part of the program
 ****/
void run(string leaked_password_file, string english_word_file){
   string password; //create varible 
   cout << "Enter password: "; // print out the prompt
   cin >> password; //have user input password

   //call each function and set equal to boolean variable
   //each one will either return true or false for password
   bool check1 = rule1(password); 
   bool check2 = rule2(password);
   bool check3 = rule3(password);
   bool check4 = rule4(password);
   bool check5 = rule5(password); 
   bool check6 = rule6(password); 
   bool check7 = rule7(password); 
   
   //if any rules are false then return error message  
   if (!check1){ 
      cout << rule_msg_1 << endl;
   }
   if (!check2){
      cout << rule_msg_2 << endl;
   }
   if (!check3){
      cout << rule_msg_3 << endl;
   }
   if (!check4){
      cout << rule_msg_4 << endl;
   }
   if (!check5){
      cout << rule_msg_5 << endl;
   }
   if (check6){
      cout << rule_msg_6 << endl;
   }
   if (!check7){
      cout << rule_msg_7 << endl;
   }

   //if rules 1-5 are true then check for rules 6 & 7
   if (check1&&check2&&check3&&check4&&check5){
      //if rules 6 & 7 return true then password is accepted
      if (!check6&&check7){
         cout << "Password accepted!" << endl;
      }
   }
}

int main() {
	/** Change the address of the files appropriatly based on your local machine.
	 * This main function will be replaced during testing. Do not add any line of code to the main function 
	 **/
	string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
	string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
	run(leaked_password_file, english_word_file);
	return 0;	
}