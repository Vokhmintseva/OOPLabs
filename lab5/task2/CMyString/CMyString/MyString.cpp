#include "MyString.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <type_traits>


MyString::MyString()
	:m_pString(new char[1])
	,m_length(0)
{
	m_pString[0] = '\0';
};

MyString::MyString(const char* pString)
	:m_length(strlen(pString))
{
	m_pString = new char[m_length + 1];
	memcpy(m_pString, pString, m_length + 1);
};

MyString::MyString(const char* pString, size_t length)
	:m_length(length)
{
	m_pString = new char[length + 1];
	m_pString[length] = '\0';
	memcpy(m_pString, pString, m_length);
};

MyString::MyString(char* pString, size_t length, Tag tag)
	:m_length(length)
	,m_pString(pString)
{}

MyString::MyString(std::string const& stlString)
	:m_length(stlString.length())
{
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
	return MyString(&m_pString[start], length);
}

MyString& MyString::operator +=(MyString const& s)
{
	char* newStr = new char[m_length + s.GetLength() + 1];
	memcpy(newStr, m_pString, m_length);
	memcpy(newStr + m_length, s.GetStringData(), s.GetLength() + 1);
	delete[] m_pString;
	m_pString = newStr;
	m_length += s.GetLength();
	return *this;
}

/*MyString operator +(MyString lhs, const MyString& rhs)
{
	return lhs += rhs;
}*/

MyString operator +(const MyString lhs, const MyString& rhs)
{
	size_t newStrLen = lhs.GetLength() + rhs.GetLength();
	char* data = new char[newStrLen + 1];
	memcpy(data, lhs.GetStringData(), lhs.GetLength());
	memcpy(data + lhs.GetLength(), rhs.GetStringData(), rhs.GetLength() + 1);
	return MyString(data, newStrLen, MyString::Tag{});
}

const char& MyString::operator[](size_t index) const
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
	size_t minLen = std::min(lhs.GetLength(), rhs.GetLength());
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
	return rhs < lhs;
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
	return !(lhs > rhs);
}

bool operator >=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs < rhs);
}

std::istream& operator>>(std::istream& stream, MyString& cstr)
{
	const size_t MAX_SIZE = 5;
	char ch;
	char buffer[MAX_SIZE + 1];
	buffer[MAX_SIZE] = '\0';
	size_t index = 0;
	while (stream.get(ch)) {
		buffer[index++] = ch;
		if (index == MAX_SIZE)
		{
			cstr += MyString(buffer, MAX_SIZE);
			index = 0;
		} 
	}
	if (index < MAX_SIZE)
	{
		buffer[index] = '\0';
		cstr += MyString(buffer, index);
	}
	return stream;
}

MyString::Iterator MyString::begin()
{
	return Iterator(m_pString);
}

MyString::Iterator MyString::end()
{
	return Iterator(m_pString + m_length);
}

MyString::ConstIterator MyString::begin() const
{
	return ConstIterator(m_pString);
}

MyString::ConstIterator MyString::end() const
{
	return ConstIterator(m_pString + m_length);
}