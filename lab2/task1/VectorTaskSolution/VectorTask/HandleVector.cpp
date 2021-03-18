#include "HandleVector.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

double getNumber(const string &str)
{
	size_t end;
	double val;
	try
	{
		val = std::stold(str, &end);
	}
	catch (const std::exception& ex)
	{
		throw std::invalid_argument("Not a number\n");
	}
	return val;
}

std::vector<double> getVector(istream& input)
{
	string str;
	string subStr;
	getline(input, str);
	istringstream strm(str);
	vector<double> array;
	while (strm >> subStr)
	{
		double num = getNumber(subStr);
		array.push_back(num);
	}
	return array;
}

double getAverage(const std::vector<double>& array)
{
	unsigned int count = 0;
	double totalSum = 0;
	std::vector<double>::const_iterator it;
	for (it = array.begin(); it != array.end(); ++it)
	{
		double dividedNum = *it / 2;
		double wholePart, fractPart;
		fractPart = std::modf(dividedNum, &wholePart);
		if (fractPart == 0.0f)
		{
			totalSum += *it;
			count++;
		}
	}
	return totalSum / count;
}

void multiplyElements(std::vector<double>& array)
{
	double average = getAverage(array);
	std::vector<double>::iterator it;
	for (it = array.begin(); it != array.end(); ++it)
	{
		double dividedNum = *it / 3;
		int whole = (int)dividedNum;
		double fractPart = dividedNum - whole;
		if (fractPart == 0.0f)
		{
			*it *= average;
		}
	}
}

void printVector(ostream& output, const std::vector<double>& array)
{
	std::vector<double>::const_iterator it;
	for (it = array.begin(); it != array.end(); ++it)
	{
		output << fixed << setprecision(3) << fixed << *it << " ";
	}
}
