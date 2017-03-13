/**
 * @author: Mitch Stark (mjs73), Zach DeCook (zjd7)
 * @date: March 6, 2017
 * @brief Prompt.h defines the Prompt class.
 */
 #include <string>
 #include <cstring>
 #include <vector>
 #include <stdio.h>
 #include <stdlib.h>
 #include <dirent.h>
 #include <unistd.h>
 using namespace std;

/**
 * @brief Maintains and manipulates your current working directory.
 */
class Prompt
{
  public:
    Prompt(){ cwd = getcwd(cwdbuf, 255); };
    string get() const{ return cwd; };
    int cd( string dir );
  private:
    string cwd;
    char cwdbuf[255];
};
