// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>
#include <string>

uint8_t ParseArgs(int argc, char* argv[])
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
    if (val < 0 || val > UINT8_MAX)
    {
        throw std::out_of_range(str + " doesn't fit byte");
    }
    return static_cast<uint8_t>(val);
}

uint8_t Reverse(uint8_t num) {
    num = (num & 0xF0) >> 4 | (num & 0x0F) << 4;
    num = (num & 0xCC) >> 2 | (num & 0x33) << 2;
    num = (num & 0xAA) >> 1 | (num & 0x55) << 1;
    return num;
}

int main(int argc, char* argv[])
{
    uint8_t byte = 0;
    try
    {
        byte = ParseArgs(argc, argv);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    uint8_t reversed = Reverse(byte);
    std::cout << (int)reversed << "\n";
    return 0;
}