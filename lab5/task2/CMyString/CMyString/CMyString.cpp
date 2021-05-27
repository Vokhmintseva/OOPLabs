// CMyString.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "MyString.h"

int main()
{
    MyString s1("Calculator");
    MyString s2("Calculator");
    bool isEquial = s1 == s2;
    std::cout << isEquial << std::endl;
}

