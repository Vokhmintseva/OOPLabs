#pragma once
#include <iostream>
#include <vector>

std::vector<double> GetVector(std::istream& input);

void MultiplyElements(std::vector<double>& array);

void PrintVector(std::ostream &output, const std::vector<double>& array);