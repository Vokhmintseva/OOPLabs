// crypt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::string searchString;
    std::string replaceString;
};

Args ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        throw std::invalid_argument("Invalid number of arguments");
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];
    return args;
}

std::string ReplaceString(std::string line, std::string searchString, std::string replaceString)
{
    size_t searchSrtLen = searchString.length();
    std::string newLine = "";
    size_t prevPos = 0;
    size_t newPos = line.find(searchString, prevPos);
    while (newPos != std::string::npos)
    {
        newLine += line.substr(prevPos, newPos - prevPos) + replaceString;
        prevPos = newPos + searchSrtLen;
        newPos = line.find(searchString, prevPos);
    }
    newLine += line.substr(prevPos);
    return newLine;
}

void ReplaceText(std::istream& input, std::ostream& output, std::string searchString, std::string replaceString)
{
    std::string line;
    while (getline(input, line))
    {
        std::string newLine = ReplaceString(line, searchString, replaceString);
        output << newLine;
        if (input.good())
        {
            output << "\n";
        }
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

    std::ifstream input(args.inputFileName);
    std::ofstream output(args.outputFileName);

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
    
    ReplaceText(input, output, args.searchString, args.replaceString);

    if (!output.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return 1;
    }
    return 0;
}
