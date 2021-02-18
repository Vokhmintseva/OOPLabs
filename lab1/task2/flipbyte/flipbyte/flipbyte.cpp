// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <string>

std::optional<std::string> parseArgs(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Invalid argument count\n";
        std::cout << "the format of command line is: flypbyte.exe <number>\n";
        return std::nullopt;
    }
    return argv[1];
}

bool isNumber(std::string inputStr)
{
    std::size_t found = inputStr.find_first_not_of("0123456789");
    bool isValid = found == std::string::npos;
    if (!isValid) {
        std::cout << "the input should be non-negative integer decimal number" << std::endl;
    }
    return isValid;
}

bool is1ByteNumber(int num)
{
    bool isValid = num >= 0 && num <= 255;
    if (!isValid) {
        std::cout << "the number should be not less then 0 and not more then 255" << std::endl;
    }
    return isValid;
}

void convertIntoBinary(int num, std::string &str)
{
    if (num != 0) {
        int remainder = num % 2;
        num = num / 2;
        convertIntoBinary(num, str);
        str +=  std::to_string(remainder);
    }
}

unsigned char reverse(unsigned char num) {
    num = (num & 0xF0) >> 4 | (num & 0x0F) << 4;
    num = (num & 0xCC) >> 2 | (num & 0x33) << 2;
    num = (num & 0xAA) >> 1 | (num & 0x55) << 1;
    return num;
}

int main(int argc, char* argv[])
{
    auto arg = parseArgs(argc, argv);
    if (!argc) {
        return 1;
    }
    
    std::string inputStr = arg->c_str();

    if (!isNumber(inputStr)) {
        return 1;
    }
     
    int decNum = std::stoi(inputStr);

    if (!is1ByteNumber(decNum)) {
        return 1;
    }

    unsigned char decNumCh = static_cast<unsigned char>(decNum);
    unsigned char reversedDecNumCh = reverse(decNumCh);
    int reversedDecNum = static_cast<int>(reversedDecNumCh);
    std::cout << reversedDecNum << "\n";
    return 0;
}

















/*bool is1byteNumber(int inputNumber)
{
    int length = 0;
    while (inputNumber != 0) {
        length++;
        inputNumber /= 10;
    }
    if (length > 8) {
        std::cout << "the number should be not less then 0 and not more then 255" << std::endl;
    }
    return length <= 8;
}*/