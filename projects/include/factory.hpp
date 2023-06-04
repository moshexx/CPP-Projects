//*****************************************************************************
//*		Descriptions - Factory API functions	    				     							
//*     Date: 15.3.21  
//*		Group: RD96						      								   
//******************************************************************************

#ifndef ILRD_RD96_FACTORY_HPP
#define ILRD_RD96_FACTORY_HPP

#include <boost/unordered_map.hpp> // boost::unordered_map
#include <boost/utility.hpp>       //boost::noncopyable

namespace ilrd
{

template <class PRODUCT, class KEY = int, class PARAM = void *, 
          class CREATOR = PRODUCT(*)(PARAM)>
class Factory : private boost::noncopyable
{
public:
    // default constructor
    // default destructor
    void AddCreator(KEY key, CREATOR creator);  // throw DoubleKey
    PRODUCT CreateObject(KEY key, PARAM param); // throw OutOfRange

    struct FactoryException : public std::exception 
    {
        virtual const char *what() const throw() = 0; 
    };

    struct OutOfRange: public FactoryException
    {
        virtual const char* what() const throw()
        {
            return "key not found";
        }
    };

    struct DoubleKey: public FactoryException
    {
        virtual const char* what() const throw()
        {
            return "The key already exists";
        }
    };

private:
    boost::unordered_map<KEY, CREATOR> m_creators;
}; // end class Factory

//******************************************************************************
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class Factory ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class PRODUCT, class KEY, class PARAM, class CREATOR>
void Factory<PRODUCT, KEY, PARAM, CREATOR>::AddCreator(KEY key, CREATOR creator)
{
    if(false == m_creators.try_emplace(key, creator).second)
    {// if the key is already existed
        throw DoubleKey();
    }
}

template <class PRODUCT, class KEY, class PARAM, class CREATOR>
PRODUCT Factory<PRODUCT, KEY, PARAM, CREATOR>::CreateObject(KEY key, PARAM param)
{
    try
    {
        return m_creators.at(key)(param);
    }
    catch(const std::out_of_range& e)
    {// throw an API exception
        throw OutOfRange();
    }
}

} //end namespace ilrd

#endif   /*ILRD_RD96_FACTORY_HPP*/
