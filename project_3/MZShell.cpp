/*
Written by: Mitch Stark
3/10/17
Purpose: Implement the MZShell class
*/

#include "MZShell.h"
#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

void MZShell::run() {
  //loop continuously until exit
  while(true) {
    cout << pr.get() << endl << "]" << flush;
    CommandLine commandline(std::cin);


    if (strcmp(commandline.getCommand(), "exit") == 0) {
      return;
    }


    //check for cd command, if found, then continue to the top of the loop
    if ((strcmp(commandline.getCommand(), "cd") == 0) && (commandline.getArgVector()[1] != NULL)) {
      int response = chdir(commandline.getArgVector(1));
      if (response < 0) {
        cout << "Can't find dir: " << commandline.getArgVector(1) << endl;
      } else {
        pr = Prompt();
      }
      continue;
    }

    //execute a "bin" command
    int index = pa.find(commandline.getCommand());
    if (index == -1) {
        continue;
    }

    char* path = (char*)pa.getDirectory(index).c_str();

    char command[261];
    char* command_dir = (char*)"/bin";
    strcpy(command, "/bin/");
    strcat(command, commandline.getCommand());

    char** vec = commandline.getArgVector();

    pid_t pid_ps = fork();
    int status;

    if (pid_ps == 0) {

        vec[commandline.getArgCount()] = NULL;
        int errno = execve(command, vec, NULL);

        if (errno == -1) {
          cout << "Unable to execute: " << commandline.getCommand() << endl;
          perror("Reason: ");
          break;
        }
    }


    if (commandline.noAmpersand()) {
      waitpid(pid_ps, &status, 0);
    }
  }
}
