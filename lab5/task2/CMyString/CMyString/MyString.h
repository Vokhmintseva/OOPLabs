#pragma once
#include <string>

class MyString
{
public:
	// конструктор по умолчанию
	MyString();

	// конструктор, инициализирующий строку данными строки с завершающим нулевым символом
	MyString(const char* pString);

	// конструктор, инициализирующий строку данными из символьного массива заданной длины
	MyString(const char* pString, size_t length);

	// конструктор копирования
	MyString(MyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11) реализуется совместно с перемещающим оператором присваивания 
	MyString(MyString&& other);

	// конструктор, инициализирующий строку данными из строки стандартной библиотеки C++
	MyString(std::string const& stlString);

	~MyString();

	size_t GetLength() const;

    const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
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