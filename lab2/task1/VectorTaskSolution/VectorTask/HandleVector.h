#pragma once
#include <iostream>
#include <vector>

std::vector<double> getVector(std::istream& input);

void multiplyElements(std::vector<double>& array);

void printVector(std::ostream &output, const std::vector<double>& array);