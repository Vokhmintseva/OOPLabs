#include "Generate.h"
#include <set>
#include <iostream>
#include <vector>

int ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Invalid number of arguments");
    }
    size_t end;
    std::string str(argv[1]);
    int val = std::stoi(str, &end);
    if (end != str.length())
    {
        throw std::invalid_argument("Not a number");
    }
    if (val < 0 || val > 100000000)
    {
        throw std::out_of_range(str + " Out of range");
    }
    return static_cast<int>(val);
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::vector<bool> sieve(upperBound, true);
    int i = 2;
    double sq = sqrt(upperBound);
    while (i <= sq)
    {
        if (sieve[i - 1] == true)
        {
            int j = pow(i, 2);
            while (j <= upperBound)
            {
                sieve[j - 1] = false;
                j = j + i;
            }
        }
        i++;
    }

    std::set<int> primeNumbers;

    for (int k = 1; k < upperBound; k++)
    {
        if (sieve[k] == true)
        {
           primeNumbers.insert(k + 1);
        }
    }

    return primeNumbers;
}

void PrintPrimeNumbers(std::ostream& output, std::set<int> primeNumbers)
{
    std::set <int>::iterator it;
    for (it = primeNumbers.begin(); it != primeNumbers.end(); ++it)
    {
        output << *it << " ";
    }
}
