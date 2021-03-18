// VectorTask.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include "HandleVector.h"

using namespace std;

int main()
{
	try
	{
		vector<double> array = getVector(cin);
		multiplyElements(array);
		sort(array.begin(), array.end());
		printVector(cout, array);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
}

