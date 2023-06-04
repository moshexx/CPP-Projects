/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: rcstring.cpp
*	author: Moshe Cohen
*	reviewer: Topaz

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <cstring>	// memcpy, strlen, strcmp
#include <cassert>	// assert
#include <stdio.h>	// BUFSIZ

#include "rcstring.hpp"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace ilrd
{
const int RCString::NULL_TERMINATOR = sizeof(char);

RCString::RCString(const char *str): m_data(Init(str)) {}	// throw std::bad_alloc

RCString::RCString(const RCString& str): m_data(str.m_data)
{
	++m_data->counter;
}

RCString::~RCString()
{
	this->RemoveInstance();
}

RCString& RCString::operator=(const RCString& rhs_)
{
	if (this != &rhs_)	// for self assignment case
	{
		this->RemoveInstance();
		this->m_data = rhs_.m_data;
		++this->m_data->counter;
	}

	return *this;
}

RCString& RCString::operator+=(const RCString& rhs_) // throw std::bad_alloc
{
	size_t thisLen = this->Length();
    size_t rhsLen = rhs_.Length() + NULL_TERMINATOR;
    size_t totalLen = thisLen + rhsLen ;

	string_data *newMData = static_cast<string_data *>(operator new
					(offsetof(string_data, flex_str) + totalLen));		  
	memcpy(newMData->flex_str, this->GetStr(), thisLen);
	memcpy(newMData->flex_str + thisLen, rhs_.GetStr(), rhsLen);
	RemoveInstance(); // --m_data->old counter;
	this->m_data = newMData;
	newMData->counter = 1;
	
	return *this;
}

char& RCString::operator[](size_t index)	// throw std::bad_alloc
{
	assert(index < Length());

	// make your own copy only if there 
	// is other pointer to your string
	if (1 < m_data->counter) 
	{
		*this = RCString(GetStr());
	}

	return m_data->flex_str[index];
}

const char& RCString::operator[](size_t index) const
{
	assert(index < Length());

	return m_data->flex_str[index];
}

const char *RCString::GetStr() const
{
    return m_data->flex_str;
}

size_t RCString::Length() const
{
	return strlen(GetStr());
}

std::ostream& operator<<(std::ostream& os_, const RCString& s_)
{
	return os_ << s_.GetStr();
}

std::istream& operator>>(std::istream& is_, RCString& s_)
{
	static char input[BUFSIZ] = {0};
	memset(input, 0, sizeof(input));

	is_ >> input;
	s_ = input; // "RemoveInstance" included

	return is_;
}

bool operator==(const RCString& lhs_, const RCString& rhs_)
{
	return 0 == strcmp(lhs_.GetStr(), rhs_.GetStr());
}

bool operator!=(const RCString& lhs_, const RCString& rhs_)
{
	return !(lhs_ == rhs_);
}

bool operator>(const RCString& lhs_,const RCString& rhs_)
{
	return strcmp(lhs_.GetStr(), rhs_.GetStr()) > 0;
}

bool operator<(const RCString& lhs_,const RCString& rhs_)
{
	return strcmp(lhs_.GetStr(), rhs_.GetStr()) < 0;
}
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

RCString::string_data *RCString::Init(const char *str) // throw std::bad_alloc
{
	assert(NULL != str);

    size_t len = strlen(str) + NULL_TERMINATOR;

    string_data *data = static_cast<string_data *>
				(operator new(offsetof(string_data, flex_str) + len));
	memcpy(data->flex_str, str, len);

	data->counter = 1;

	return data;
}

void RCString::RemoveInstance()
{
	--m_data->counter;
	if (0 == m_data->counter)
	{
		delete m_data;
	}
}

}//namespace ilrd

