// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "StringList.h"

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    auto iter = v.begin(); 
    iter--;
    iter--;
    iter--;
    iter = v.begin();
    while (iter != v.end())    // пока не дойдем до конца
    {
        std::cout << *iter << std::endl;// получаем элементы через итератор
        ++iter;             // перемещаемся вперед на один элемент
    }
	return 0;
}