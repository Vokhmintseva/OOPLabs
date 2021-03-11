#pragma once
#include <string>
#include <iostream>
#include <set>
#include <optional>

int ParseArgs(int argc, char* argv[]);

std::set<int> GeneratePrimeNumbersSet(int upperBound);

void PrintPrimeNumbers(std::ostream& output, std::set<int> primeNumbers);