#pragma once
#include <iostream>
#include <string>

std::string HtmlDecode(std::string const& html);

void DecodeLines(std::istream& input, std::ostream& output);