/*
Written by: Mitch Stark mjs73, Zach DeCook (zjd7)
3/10/17
Purpose: Define the MZShell class
*/
#include "CommandLine.h"
#include "Path.h"
#include "Prompt.h"
#include <sys/wait.h>

class MZShell {
private:
  Prompt pr;
  Path pa;

public:
  //initialize the shell
  MZShell() {};

  //run the shell
  void run();
};
