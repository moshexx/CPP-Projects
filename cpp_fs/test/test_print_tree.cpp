/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_print_tree.cpp
*	author: Moshe Cohen
*	reviewer: TODO:

--------------------------------------------------------------------------------
*******************************************************************************/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>
#include <cstring>
#include <cassert>
#include <dirent.h>		// d_type, readdir
#include <sys/stat.h>	// S_ISDIR

#include "print_tree.hpp"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
using namespace ilrd;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "argv[1] is needed" << std::endl;

        return 1;
    }

    DIR *folder = opendir(argv[1]);
    if(NULL == folder)
    {
        std::cerr << argv[1] << "   [error opening dir] " << std::endl;
        closedir(folder);
        
        return 1;
    }
    closedir(folder);

    Dir dir(argv[1]);
    dir.Print();    


	return 0;
}
