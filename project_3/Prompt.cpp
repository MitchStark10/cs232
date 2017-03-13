/**
 * @author: Mitch Stark (mjs73), Zach DeCook (zjd7)
 * @date: March 11, 2017
 * @brief Prompt.cpp implements the Path class.
 */
#include "Prompt.h"

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
