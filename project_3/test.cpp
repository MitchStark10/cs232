/**
 * @author: Mitch Stark (mjs73), Zach DeCook (zjd7)
 * @date: March 6, 2017
 * @brief test.cpp tests classes to make sure they are compliant.
 */
#include <string>
#include <iostream>
#include "Path.h"
#include "Prompt.h"

using namespace std;

int main()
{
  cout << "hello\n";

  cout << "testing Path constructor...\n";
  Path path;
  cout << "Path created.\n";

  cout << "testing Path::find() for failure...\n";
  int index = -1;
  string command = "sls";
  index = path.find(command);
  if ( index == -1 )
  {
    cout << command << " not found\n";
  }
  else
  {
    cout << command << " found at " << index << ".\n";
  }

  cout << "testing Path::find() for success...\n";
  command = "ls";
  index = path.find(command);
  if ( index == -1 )
  {
    cout << command << " not found\n";
    return 1;
  }
  else
  {
    cout << command << " found at " << index << ".\n";
  }

  cout << "testing Path::getDirectory()...\n";
  string directory;
  directory = path.getDirectory( index );
  cout << "Directory at " << index << " was " << directory << "\n";

  cout << "testing Path::getDirectory() for exceptions...\n";
  try
  {
    directory = path.getDirectory( -1 );
  }
  catch ( out_of_range e )
  {
    cout << "Exception rightfully caught: '" << e.what() << "'.\n";
  }

  cout << "testing Prompt constructor...\n";
  Prompt my_prompt;
  cout << "prompt created\n";

  cout << "testing Prompt::get()...\n";
  cout << "cwd is: " << my_prompt.get() << "\n";

  cout << "testing Prompt::cd()...\n";
  my_prompt.cd( ".." );
  cout << "cwd is: " << my_prompt.get() << "\n";
  my_prompt.cd( "../.." );
  cout << "cwd is: " << my_prompt.get() << "\n";

  cout << "testing Prompt::cd() for failure...\n";
  if ( my_prompt.cd( "123/21/55" ) != 0 )
  {
    cout << "Correctly couldn't change directories\n";
  }
  else
  {
    cout << "Failure to change directories not detected\n";
  }
  cout << "cwd is: " << my_prompt.get() << "\n";

  return 0;
}
