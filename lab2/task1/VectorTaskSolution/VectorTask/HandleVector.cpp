#include "HandleVector.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>

using namespace std;

std::vector<double> GetVector(istream& input)
{
	string str;
	string subStr;
	getline(input, str);
	istringstream strm(str);
	vector<double> array;
	double num;
	while (strm >> num)
	{
		array.push_back(num);
	}
	if (!strm.eof())
	{
		throw std::invalid_argument("Not a number\n");
	}
	return array;
}

double GetAverageEvens(const std::vector<double>& array)
{
	unsigned int count = 0;
	double totalSum = 0;
	for (double val: array)
	{
		if (std::fmod(val, 2) == 0)
		{
			totalSum += val;
			++count;
		}
	}
	double ave = totalSum / count;
	std::cout << ave << std::endl;
	return totalSum / count;
}

void MultiplyElements(std::vector<double>& array)
{
	double average = GetAverageEvens(array);
	std::transform(begin(array), end(array), begin(array),
		[average](double number)
		{
			return std::fmod(number, 3) == 0 ? number *= average : number;
		}
	);
}

void PrintVector(ostream& output, const std::vector<double>& array)
{
	output.setf(std::ios::fixed);
	output.precision(3);
	std::copy(array.begin(), array.end(), ostream_iterator<double>(output, " "));
}
