// main.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
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
    while (iter != v.end())    // ���� �� ������ �� �����
    {
        std::cout << *iter << std::endl;// �������� �������� ����� ��������
        ++iter;             // ������������ ������ �� ���� �������
    }
	return 0;
}