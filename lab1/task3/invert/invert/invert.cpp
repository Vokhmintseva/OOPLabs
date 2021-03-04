// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <optional>
#include <string>
#include <regex>
#include <math.h>
#include <array>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

std::optional<std::string> ParseArgs(int argc, char* argv[])
{
    if (argc != 2) 
    {
        return std::nullopt;
    }
    return argv[1];
}

double GetAddition(const Matrix3x3& m, int row, int col)
{
    double b[2][2];
    int i, j, bi, bj;
    bj = 0;
    for (i = 0, bi = 0; i < 3; i++)
    {
        if (i != row)
        {
            for (j = 0, bj = 0; j < 3; j++)
            {
                if (j != col)
                {
                    b[bi][bj] = m[i][j];
                    bj++;
                }
            }
            bi++;
        }
    }
    return pow(-1, row + col) * (b[0][0] * b[1][1] - b[0][1] * b[1][0]);
}

double CalcDeterminant(const Matrix3x3& m, int col)
{
    double determinant = 0.0f;
    for (int j = 0; j < col; j++)
    {
         determinant += m[0][j] * GetAddition(m, 0, j);
    }
    return determinant;
}

void PrintMatrixСoeffs(const Matrix3x3& m, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) 
        {
            printf("%-10.3f", m[i][j]);
        }
        std::cout << "\n";
    }
}

void TransposeMatrix(Matrix3x3 &m, int row, int col)
{
    double curValue;
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < col; j++)
        {
            std::swap(m[i][j], m[j][i]);
        }
    }
}

std::optional<Matrix3x3> Invert(Matrix3x3 &m, int row, int col)
{
    double determinant = CalcDeterminant(m, 3);
    if (determinant == 0.0f)
    {
        return std::nullopt;
    }
    
    Matrix3x3 currMatrix;
    for (int i = 0; i < row; i++) 
    {
        for (int j = 0; j < col; j++) 
        {
            currMatrix[i][j] = GetAddition(m, i, j) / determinant;
        }
    }
    TransposeMatrix(currMatrix, row, col);
    return currMatrix;
}

bool IsValidStr(std::string str) 
{
    static const std::regex r("^-{0,1}\\d+(\\.\\d+)?\\s+-{0,1}\\d+(\\.\\d+)?\\s+-{0,1}\\d+(\\.\\d+)?$");
    return regex_match(str, r);
}

void ReadMatrix(Matrix3x3& matrix, std::ifstream& inputFile, int row, int col)
{
    uint8_t strCounter = 0;
    std::string line;
    while (getline(inputFile, line))
    {
        strCounter++;
        if (strCounter > row)
        {
            inputFile.close();
            throw std::invalid_argument("There are too many lines in the input file\n");
        }
        if (!IsValidStr(line))
        {
            inputFile.close();
            throw std::invalid_argument("There is incorrect line in the input file\n");
        }

        std::stringstream strm(line);
        for (int j = 0; j < col; j++) 
        {
            strm >> matrix[strCounter - 1][j];
        }
    }
    inputFile.close();
    if (strCounter != row)
    {
        throw std::invalid_argument("The input file lacks lines\n");
    }
}

int main(int argc, char* argv[])
{
    auto arg = ParseArgs(argc, argv);
    if (!arg) {
        std::cout << "Invalid argument count\n";
        std::cout << "the format of command line is: invert.exe <matrix.txt>\n";
        return 1;
    }

    std::ifstream inputFile;
    inputFile.open(arg->c_str());
    if (!inputFile.is_open()) 
    {
        std::cout << "Failed to open '" << arg->c_str() << "' for reading\n";
        return 1;
    }

    Matrix3x3 matrix;
    try
    {
        ReadMatrix(matrix, inputFile, 3, 3);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    auto invertedMatrix = Invert (matrix, 3, 3);
    if (!invertedMatrix)
    {
        std::cout << "The matrix is non-invertible\n" << std::endl;
        return 1;
    }
    PrintMatrixСoeffs(*invertedMatrix, 3, 3);
    return 0;
}