/**
 * @author: Zach DeCook (zjd7)
 * @date: March 6, 2017
 * @brief pathprompt.cpp defines the Path and Prompt classes.
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

/**
 * @brief Change directories
 * @return 0 if successful, -1 if failed.
 */
int Prompt::cd( string dir )
{
  int success;
  success = chdir( dir.c_str() );
  if( success == 0 )
  {
    cwd = getcwd(cwdbuf, 255);
    return 0;
  }
  else
  {
    return -1;
  }
};

/**
 * @brief Initialize Path, store all executable paths in a private variable.
 */
Path::Path()
{
  string dirs = getenv( "PATH" );
  string a_path = "";
  for( int i = 0; i < dirs.length(); i++ )
  {
    if ( dirs[i] == ':' )
    {
      directories.push_back( a_path );
      a_path = "";
    }
    else
    {
      a_path += dirs[i];
    }
  }
}

/**
 * @brief finds the directory in which a given program is stored.
 * @param const string& program The program name.
 * @return int The address of the directory in this Path, or -1 if nonexistent.
 */
int Path::find( const string& program ) const
{
  DIR * dirp;
  struct dirent * dp;
  for( int i = 0; i < directories.size(); i++ )
  {
    dirp = opendir( directories[i].c_str() );
    if ( dirp != NULL )
    {
      while ( dp = readdir( dirp ) )
      {
        if (strlen(dp->d_name) == program.length()
          && program.compare(dp->d_name) == 0)
        {
          (void)closedir(dirp);
          return i;
        }
      }
    }
    (void)closedir(dirp);
  }
  return -1;
}

/**
 * @brief return the directory at position i in this Path.
 * @precondition There is an element i in our Path.
 */
string Path::getDirectory( int i ) const
{
  return directories[i];
}

