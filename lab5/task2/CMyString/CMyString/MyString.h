#pragma once
#include <string>

class MyString
{
public:
	// ����������� �� ���������
	MyString();

	// �����������, ���������������� ������ ������� ������ � ����������� ������� ��������
	MyString(const char* pString);

	// �����������, ���������������� ������ ������� �� ����������� ������� �������� �����
	MyString(const char* pString, size_t length);

	// ����������� �����������
	MyString(MyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11) ����������� ��������� � ������������ ���������� ������������ 
	MyString(MyString&& other);

	// �����������, ���������������� ������ ������� �� ������ ����������� ���������� C++
	MyString(std::string const& stlString);

	~MyString();

	size_t GetLength() const;

    const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	MyString& operator =(MyString const& s);
	MyString& operator =(MyString && s);
	MyString& operator +=(MyString const& s);
	const char& operator[](size_t index)const;
	char& operator[](size_t index);
	MyString friend operator +(const MyString lhs, const MyString& rhs);
private:
	struct Tag {};
	MyString(char* pString, size_t length, Tag tag);
	char* m_pString;
	size_t m_length;
};
bool operator <(const MyString& lhs, const MyString& rhs);
bool operator >(const MyString& lhs, const MyString& rhs);
bool operator ==(const MyString& lhs, const MyString& rhs);
bool operator !=(const MyString& lhs, const MyString& rhs);
bool operator <=(const MyString& lhs, const MyString& rhs);
bool operator >=(const MyString& lhs, const MyString& rhs);
MyString operator +(const MyString lhs, const MyString& rhs);
std::ostream& operator<<(std::ostream& stream, MyString const& cstr);
std::istream& operator>>(std::istream& stream, MyString& cstr);