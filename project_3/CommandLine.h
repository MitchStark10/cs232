/*
Written by: Mitch Stark mjs73, Zach DeCook (zjd7)
3/10/17
Purpose: Implement the CommandLine class
*/

#include<iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

class CommandLine {
  vector<string> tokens;
 public:
  //initialize the class
  CommandLine(std::istream& in) {
    char* command_string = new char[256];
    in.getline(command_string, 256);

    if (strcmp(command_string, "") == 0) {
        tokens.push_back("");
    }

    stringstream ss(command_string);
    string buf;
    while (ss >> buf) tokens.push_back(buf);
  };

  ~CommandLine() {
      delete command_string;
  }
  //gets the first word in the string
  char* getCommand() const;

  //gets the number of arguments provided
  int getArgCount() const;

  //gets a pointer to an array of the strings
  char** getArgVector() const;

  //returns a specific word in the vector
  char* getArgVector(int i) const;

  //checks if there is an amperstand in the string
  bool noAmpersand() const;
};
