#include "MyString.h"
#include <stdexcept>
#include <iostream>
#include <cassert>

MyString::MyString()
	:m_pString(new char[1])
	,m_length(0)
{
	m_pString[0] = '\0';
};

MyString::MyString(const char* pString)
	:m_length(strlen(pString))
{
	//std::cout << "constructor MyString(const char* pString)" << std::endl;
	m_pString = new char[m_length + 1];
	memcpy(m_pString, pString, m_length + 1);
};

MyString::MyString(const char* pString, size_t length)
	:m_length(length)
{
	//std::cout << "constructor MyString(const char* pString, size_t length)" << std::endl;
	m_pString = new char[length + 1];
	memset(&m_pString[length], '\0', sizeof(char));
	memcpy(m_pString, pString, m_length);
};

MyString::MyString(std::string const& stlString)
	:m_length(stlString.length())
{
	//std::cout << "constructor MyString(std::string const& stlString)" << std::endl;
	m_pString = new char[m_length + 1];
	memcpy(m_pString, stlString.c_str(), m_length + 1);
};

MyString::MyString(MyString const& other)
	:m_pString(new char[other.GetLength() + 1])
	,m_length(other.GetLength())
{
	memcpy(m_pString, other.GetStringData(), m_length + 1);
};

MyString::MyString(MyString&& other)
	:m_pString(other.m_pString)
	, m_length(other.m_length)
{
	other.m_pString = nullptr;
	other.m_length = 0;
};

MyString& MyString::operator=(MyString && s)
{
	if (std::addressof(s) != this)
	{
		delete[] m_pString;
		m_pString = s.m_pString;
		m_length = s.m_length;
		s.m_pString = nullptr;
		s.m_length = 0;
	}
	return *this;
}

MyString::~MyString()
{
	delete[] m_pString;
}

char const* MyString::GetStringData() const
{
	return m_pString;
}

size_t MyString::GetLength() const
{
	return m_length;
}

MyString& MyString::operator=(MyString const& s)
{
	if (std::addressof(s) != this)
	{
		MyString tmp(s);
		std::swap(m_pString, tmp.m_pString);
		std::swap(m_length, tmp.m_length);
	}
	return *this;
}

void MyString::Clear()
{
	m_pString[0] = '\0';
	m_length = 0;
}

MyString MyString::SubString(size_t start, size_t length) const
{
	if (m_length < start + length)
	{
		throw std::out_of_range("");
	}
	if (length == 0)
	{
		throw std::invalid_argument("");
	}
	return MyString(&m_pString[start], length);
}

MyString& MyString::operator +=(MyString const& s)
{
	char* newStr = new char[m_length + strlen(s.GetStringData()) + 1];
	memcpy(newStr, m_pString, m_length);
	memcpy(newStr + m_length, s.GetStringData(), s.GetLength() + 1);
	delete[] m_pString;
	m_pString = newStr;
	m_length += strlen(s.GetStringData());
	return *this;
}

const char& MyString::operator[](size_t index)const
{
	if (index >= m_length)
	{
		throw std::out_of_range("The index is out of range");
	}
	return m_pString[index];
}

char& MyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("The index is out of range");
	}
	return m_pString[index];
}

bool operator <(const MyString& lhs, const MyString& rhs)
{
	size_t minLen = lhs.GetLength() <= rhs.GetLength() ? lhs.GetLength() : rhs.GetLength();
	for (size_t i = 0; i < minLen; i++)
	{
		if (lhs.GetStringData()[i] < rhs.GetStringData()[i])
		{
			return true;
		}
		else if (lhs.GetStringData()[i] > rhs.GetStringData()[i])
		{
			return false;
		}
	}
	return lhs.GetLength() < rhs.GetLength();
}

bool operator >(const MyString& lhs, const MyString& rhs)
{
	return lhs != rhs && !(lhs < rhs);
}

bool operator ==(const MyString& lhs, const MyString& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}
	for (size_t i = 0; i <= lhs.GetLength(); i++)
	{
		if (lhs.GetStringData()[i] != rhs.GetStringData()[i])
		{
			return false;
		}
	}
	return true;
}

bool operator !=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

const MyString operator +(MyString lhs, const MyString& rhs)
{
	return lhs += rhs;
}

std::ostream& operator<<(std::ostream& stream, MyString const& cstr)
{
	for (size_t i = 0; i < cstr.GetLength(); i++)
	{
		if (cstr[i] != '\0')
		{
			stream << cstr[i];
		}
	}
	return stream;
}

bool operator <=(const MyString& lhs, const MyString& rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator >=(const MyString& lhs, const MyString& rhs)
{
	return lhs == rhs || lhs > rhs;
}

std::istream& operator>>(std::istream& stream, MyString& cstr)
{
	const size_t MAX_SIZE = 150;
	char ch;
	char buffer[MAX_SIZE + 1];
	buffer[MAX_SIZE] = '\0';
	size_t index = 0;
	while (stream.get(ch)) {
		buffer[index++] = ch;
		if (index == MAX_SIZE)
		{
			cstr += buffer;
			index = 0;
		} 
	}
	if (index < MAX_SIZE)
	{
		buffer[index] = '\0';
		cstr += buffer;
	}
	return stream;
}
