/**
 * @author: Mitch Stark (mjs73), Zach DeCook (zjd7)
 * @date: March 6, 2017
 * @brief Path.h defines the Path class.
 */
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
using namespace std;

/**
 * @brief Keeps track of directories in your executable path.
 *  Searches for programs in these paths.
 */
class Path
{
  public:
    Path();
    int find( const string& program ) const;
    string getDirectory( int i ) const;
  private:
    vector<string> directories;
};
