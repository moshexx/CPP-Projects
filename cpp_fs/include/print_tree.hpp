/*******************************************************************************
*	    Descriptions - Print Tree                                              *
*		Date: 18.2.20                                                          *
*       Group: RD96                                                            * 
*                                                                              *
*******************************************************************************/
#ifndef __ILRD_RD96_PRINT_TREE_HPP__
#define __ILRD_RD96_PRINT_TREE_HPP__ 

#include <vector> // vector
#include <string> // std::string

#include "util.hpp" //uncopyable

namespace ilrd
{
class File : private Uncopyable
{
public:
    explicit File(const std::string name, size_t offset = 0);
    virtual ~File();
    virtual void Print() const = 0;
    std::string GetName() const;
    size_t GetOffset() const;
private:
    size_t m_offset;
    const std::string m_name;
};

class Dir : public File
{
public:
    explicit Dir(const std::string name, size_t offset = 0); 
    virtual ~Dir();
    virtual void Print() const;
private:
    std::vector<File *> m_files;
};

class RegFile : public File
{
public:
    explicit RegFile(const std::string name, size_t offset = 0);
    virtual ~RegFile();
    virtual void Print() const;
};
} // end namespace ilrd

 #endif   /*__ILRD_RD96_PRINT_TREE_HPP__ */

