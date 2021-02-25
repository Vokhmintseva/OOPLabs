// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> parseArgs(int argc, char* argv[])
{
    if (argc != 2) {
        return std::nullopt;
    }
    return argv[1];
}

uint8_t reverse(uint8_t num) {
    num = (num & 0xF0) >> 4 | (num & 0x0F) << 4;
    num = (num & 0xCC) >> 2 | (num & 0x33) << 2;
    num = (num & 0xAA) >> 1 | (num & 0x55) << 1;
    return num;
}

uint8_t ParseByte(const std::string& str)
{
    size_t end;
    int val = std::stoi(str, &end);
    if (end != str.length())
    {
        throw std::invalid_argument("Not a number");
    }
    if (val < 0 || val > UINT8_MAX)
    {
        throw std::out_of_range(str + " doesn't fit to byte");
    }
    return static_cast<uint8_t>(val);
}

int main(int argc, char* argv[])
{
    auto arg = parseArgs(argc, argv);
    if (!arg) {
        std::cout << "Invalid argument count\n";
        std::cout << "the format of command line is: flypbyte.exe <number>\n";
        return 1;
    }
    uint8_t byte = 0;
    try
    {
        byte = ParseByte(arg->c_str());
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    uint8_t reversed = reverse(byte);
    std::cout << (int)reversed << "\n";
    return 0;
}

