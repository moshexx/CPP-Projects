/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: print_tree.cpp
*	author: Moshe Cohen
*	reviewer: Lidor

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>       // std::vector
#include <dirent.h>		// d_type, readdir
#include <sys/stat.h>	// S_ISDIR 

#include "print_tree.hpp"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const char *BLUE_B 	= "\033[01;34m";
const char *WHITE_B = "\033[01;37m";
const char *RESET 	= "\033[0m";

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace ilrd
{
	namespace //detail
	{ 
	static void PrintLine(size_t offset)
    {
        for(size_t i = 0; i < offset; ++i)
        {
            if(0 == i % 3)
            {
                std::cout << "│";  
            }
            else
            {
                std::cout << " ";
            }
        }
    }

    static void DeleteForEach(File *file)
    {  
        delete file;
    }	

	static void PrintForEach(File *file)
    {  
        file->Print();
    }

	} //end namespace detail

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ File ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    File::File(const std::string name, size_t offset): 
	m_offset(offset),
	m_name(name)
	{ //empty body
	}

	File::~File()
	{//empty function
	}

	std::string File::GetName() const
	{
		return m_name;
	}

	size_t File::GetOffset() const
	{
		return m_offset;
	}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Dir ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Dir::Dir(const std::string name, size_t offset): File(name, offset) // throw std::runtime_error
{																	// exception safety: no garantee
    DIR *folder = opendir(name.c_str());

    if(NULL == folder)
    {
        std::cerr << "Unable to read directory " << name << std::endl;
        throw std::runtime_error("Unable to read directory");
    }

    /* Read directory entries */
    struct dirent *entry = readdir(folder);
	std::string nextEntryPath;
    while (NULL != entry)
    {
		nextEntryPath = name + "/" + entry->d_name;

		if ('.' != entry->d_name[0])
		{
			m_files.push_back(NULL);
			if (DT_DIR == entry->d_type)
			{// Directory
				m_files.back() = new Dir(nextEntryPath, GetOffset() + 3); 
			}
			else
			{// RegFile
				m_files.back() = new RegFile(nextEntryPath, GetOffset() + 3); 
			}
		}

		entry = readdir(folder);
    }

    closedir(folder);
}

Dir::~Dir()
{
	for_each(m_files.begin(), m_files.end(), DeleteForEach);
}

void Dir::Print() const
{
	size_t offset = GetOffset();

	if (0 == offset)
	{
		std::cout << BLUE_B << GetName() << RESET << std::endl;
		PrintLine(offset);
	}
	else
	{
		PrintLine(offset);
		// print the first name from the full path
		size_t found = GetName().find_last_of("/");
		std::cout <<"├─ "<< BLUE_B << GetName().substr(found + 1) << RESET <<std::endl;
	}

	// print the enteries in the directory
	for_each(m_files.begin(), m_files.end(), PrintForEach);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RegFile ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
RegFile::RegFile(const std::string name, size_t offset):
File(name, offset)
{// empty body
}

RegFile::~RegFile()
{// empty body
}

void RegFile::Print() const
{
	PrintLine(GetOffset());
	
	size_t found = GetName().find_last_of("/");
    std::cout <<"├─ "<< WHITE_B << GetName().substr(found + 1) << RESET <<std::endl;
}

} //end namespace ilrd