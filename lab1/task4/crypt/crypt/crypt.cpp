// crypt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <string>

enum Command {
    Crypt,
    Decrypt
};

struct Args
{
    Command command;
    std::string inputFileName;
    std::string outputFileName;
    char key;
};

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        throw std::invalid_argument("Invalid number of arguments");
    }
    
    Args args;

    std::string argv1(argv[1]);
    if (argv1 == "crypt")
    {
        args.command = Crypt;
    }
    else if (argv1 == "decrypt")
    {
        args.command = Decrypt;
    }
    else
    {
        throw std::invalid_argument("Not a valid command: expected either 'crypt' or 'decrypt' one");
    }

    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    
    size_t end;
    std::string argv4(argv[4]);
    int mask = std::stoi(argv4, &end);
    if (end != argv4.length())
    {
        throw std::invalid_argument("Key isn't a number");
    }
    if (mask < 0 || mask > UINT8_MAX)
    {
        throw std::out_of_range(argv4 + " doesn't fit byte");
    }
    args.key = mask;

    return args;
}

char EncryptChar(char byte)
{
    char b012 = (byte & 0b00000111) << 2;
    char b34 = (byte & 0b00011000) << 3;
    char b56 = (byte & 0b01100000) >> 5;
    char b7 = (byte & 0x80) >> 2;
    return b012 | b34 | b56 | b7;
}

char DecryptChar(char byte)
{
    char b01 = (byte & 0b00000011) << 5;
    char b234 = (byte & 0b00011100) >> 2;
    char b5 = (byte & 0b00100000) << 2;
    char b67 = (byte & 0b11000000) >> 3;
    return b01 | b234 | b5 | b67;
}

void EncryptFile(std::istream& input, std::ostream& output, char key)
{
    char ch;
    while (input.read(&ch, sizeof(char)))
    {
        ch ^= key;
        ch = EncryptChar(ch);
        output.write(&ch, sizeof(char));
    }
}

void DecryptFile(std::istream& input, std::ostream& output, char key)
{
    char ch;
    while (input.read(&ch, sizeof(char)))
    {
        ch = DecryptChar(ch);
        ch ^= key;
        output.write(&ch, sizeof(char));
    }
}

int main(int argc, char* argv[])
{
    Args args;
    try
    {
        args = ParseArgs(argc, argv);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    std::ifstream input(args.inputFileName, std::ios_base::binary); 
    std::ofstream output(args.outputFileName, std::ios_base::binary);
    
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args.inputFileName << "' for reading\n";
        return 1;
    }
    
    if (!output.is_open()) 
    {
        std::cout << "Failed to open '" << args.outputFileName << "' for writing\n";
        return 1;
    }

    char key = args.key;
    if (args.command == Crypt)
    {
        EncryptFile(input, output, key);
    }
    else if (args.command == Decrypt)
    {
        DecryptFile(input, output, key);
    }

    return 0;
}
