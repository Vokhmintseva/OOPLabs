#pragma once
#include <string>

class MyString
{
public:
	friend class Iterator;
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

	class Iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = char;
		using pointer = char*;
		using reference = char&;

		Iterator(pointer ptr = nullptr)
			: m_ptr(ptr)
		{}

		bool operator!=(const Iterator& other) const
		{
			return m_ptr != other.m_ptr;
		}

		bool operator==(const Iterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		Iterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			++* this;
			return temp;
		}

		Iterator operator--(int)
		{
			Iterator temp = *this;
			--* this;
			return temp;
		}

		Iterator& operator--()
		{
			--m_ptr;
			return *this;
		}
	private:
		char* m_ptr;
	};

	class ConstIterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = const char;
		using pointer = const char*;
		using reference = const char&;

		ConstIterator(pointer ptr = nullptr)
			: m_ptr(ptr)
		{}

		bool operator!=(const ConstIterator& other) const
		{
			return m_ptr != other.m_ptr;
		}

		bool operator==(const ConstIterator& other) const
		{
			return m_ptr == other.m_ptr;
		}

		reference operator*() const
		{
			return *m_ptr;
		}

		pointer operator->() const
		{
			return m_ptr;
		}

		ConstIterator& operator++()
		{
			++m_ptr;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator temp = *this;
			++* this;
			return temp;
		}

		ConstIterator operator--(int)
		{
			ConstIterator temp = *this;
			--* this;
			return temp;
		}

		ConstIterator& operator--()
		{
			--m_ptr;
			return *this;
		}
	private:
		const char* m_ptr;
	};

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	
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