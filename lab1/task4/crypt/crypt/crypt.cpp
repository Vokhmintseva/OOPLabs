// crypt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
    std::string command;
    std::string inputFileName;
    std::string outputFileName;
    std::string key;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        return std::nullopt;
    }
    Args args;
    args.command = argv[1];
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    args.key = argv[4];
    return args;
}

char crypt(char byte)
{
    char b0 = byte;
    b0 = (b0 & 0x01) << 2;
    char b1 = byte;
    b1 = (b1 & 0x02) << 2;
    char b2 = byte;
    b2 = (b2 & 0x04) << 2;
    char b3 = byte;
    b3 = (b3 & 0x08) << 3;
    char b4 = byte;
    b4 = (b4 & 0x10) << 3;
    char b5 = byte;
    b5 = (b5 & 0x20) >> 5;
    char b6 = byte;
    b6 = (b6 & 0x40) >> 5;
    char b7 = byte;
    b7 = (b7 & 0x80) >> 2;
    return b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
}

char decrypt(char byte)
{
    char b0 = byte;
    b0 = (b0 & 0x01) << 5;
    char b1 = byte;
    b1 = (b1 & 0x02) << 5;
    char b2 = byte;
    b2 = (b2 & 0x04) >> 2;
    char b3 = byte;
    b3 = (b3 & 0x08) >> 2;
    char b4 = byte;
    b4 = (b4 & 0x10) >> 2;
    char b5 = byte;
    b5 = (b5 & 0x20) << 2;
    char b6 = byte;
    b6 = (b6 & 0x40) >> 3;
    char b7 = byte;
    b7 = (b7 & 0x80) >> 3;
    return b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
}

void CheckArgs(std::string command, std::string key)
{
    if (command != "crypt" && command != "decrypt")
    {
        throw std::invalid_argument("Not a valid command: expected either 'crypt' or 'decrypt' one");
    }
    size_t end;
    int val = std::stoi(key, &end);
    if (end != key.length())
    {
        throw std::invalid_argument("Key isn't a number");
    }
    if (val < 0 || val > UINT8_MAX)
    {
        throw std::out_of_range(key + " doesn't fit byte");
    }
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!argc) {
        std::cout << "Invalid argument count\n";
        std::cout << "Usage: copyFile.exe crypt|decrypt <input file name> <output file name> <key>\n";
        return 1;
    }
            
    try
    {
        CheckArgs(args->command, args->key);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    std::fstream input(args->inputFileName, std::ios_base::in|std::ios_base::binary); 
    std::fstream output(args->outputFileName, std::ios::out|std::ios::binary);
    
    if (!input.is_open()) {
        std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }
    
    if (!output.is_open()) {
        std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    char key = static_cast<char>(stoi(args->key));
    char ch;
    
    if (args->command == "crypt")
    {
        while (input.read(&ch, sizeof(char)))
        {
            ch ^= key;
            ch = crypt(ch);
            output.write(&ch, sizeof(char));
        }
    } else if (args->command == "decrypt")
    {
        while (input.read(&ch, sizeof(char)))
        {
            ch = decrypt(ch);
            ch ^= key;
            output.write(&ch, sizeof(char));
        }
    }

    input.close();
    output.close();
    return 0;
}


//std::cout << std::bitset<8>(newCh);