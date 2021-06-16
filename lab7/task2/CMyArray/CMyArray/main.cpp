// CMyArray.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> array{ 12, 10, 8, 6, 4, 2, 1 };
    auto it = array.end();
    std::cout << *it << std::endl;


    return 0;
}

