// FindMaxEx.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include "FindMaxEx.h"

int main()
{
    std::vector<Sportsman> sportsmanVector = 
    {
        {"some sportsman1", 28, 80},
        {"some sportsman2", 35, 75},
        {"some sportsman3", 45, 95},
    };

    Sportsman s;

    FindMax<Sportsman>(sportsmanVector, s, CompareSportsmenWeight());
    std::cout << s.fullName << std::endl;

    FindMax<Sportsman>(sportsmanVector, s, CompareSportsmenAge());
    std::cout << s.fullName << std::endl;
}

