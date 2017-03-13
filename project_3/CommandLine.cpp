/*
Written by: Mitch Stark mjs73, Zach DeCook (zjd7)
3/10/17
Purpose: Define the CommandLine class
*/
#include "CommandLine.h"

char* CommandLine::getCommand() const {
  return (char*)tokens[0].c_str();
}

int CommandLine::getArgCount() const {
  return tokens.size();
}

char** CommandLine::getArgVector() const {
  //return tokens;
  char** arr = new char*[tokens.size()];
  for(int i = 0; i < tokens.size(); i++) {
    if (strcmp(tokens[i].c_str(), "&") != 0) {
        arr[i] = (char*)tokens[i].c_str();
    }

  }
  return arr;
}

char* CommandLine::getArgVector(int i) const {
  return (char*)tokens[i].c_str();
}

bool CommandLine::noAmpersand() const {
  for(int i = 0; i < tokens.size(); i++) {
    if (tokens[i].find("&") != string::npos) {
      return false;
    }
  }
  return true;
}
