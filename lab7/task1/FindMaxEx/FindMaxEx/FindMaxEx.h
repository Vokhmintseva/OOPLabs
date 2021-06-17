#pragma once
#include <string>
#include <vector>

template <typename T>
class Less
{
public:
	bool operator() (T const& a, T const& b) const
	{
		return a < b;
	}
};

template <>
class Less<const char*>
{
public:
	bool operator() (const char* const& a, const char* const& b) const
	{
		return strcmp(a, b) < 0;
	}
};

struct Sportsman
{
	std::string fullName;
	unsigned short age;
	unsigned short weight;
};

class CompareSportsmenWeight
{
public:
	bool operator()(const Sportsman& a, const Sportsman& b) const
	{
		return a.weight < b.weight;
	}
};

class CompareSportsmenAge
{
public:
	bool operator()(const Sportsman& a, const Sportsman& b) const
	{
		return a.age < b.age;
	}
};

template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.begin() == arr.end())
	{
		return false;
	}
	auto largest = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		if (less(*largest, *it)) {
			largest = it;
		}
	}
	maxValue = *largest;
	return true;
}
