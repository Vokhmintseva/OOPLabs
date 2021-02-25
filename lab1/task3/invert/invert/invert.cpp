// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <optional>
#include <string>
#include <regex>
#include <math.h>

std::optional<std::string> parseArgs(int argc, char* argv[])
{
    if (argc != 2) {
        return std::nullopt;
    }
    return argv[1];
}

float getAddition(float* m[], int row, int col)
{
    float b[2][2];
    int i, j, bi, bj;
    bj = 0;
    for (i = 0, bi = 0; i < 3; i++)
    {
        if (i != row)
        {
            for (j = 0, bj = 0; j < 3; j++)
                if (j != col)
                {
                    b[bi][bj] = m[i][j];
                    bj++;
                }
            bi++;
        }
    }
    return pow(-1, row + col) * (b[0][0] * b[1][1] - b[0][1] * b[1][0]);
}

float calcDeterminant(float* m[])
{
    float determinant = 0.0f;
    for (int j = 0; j < 3; j++)
    {
         determinant += m[0][j] * getAddition(m, 0, j);
    }
    return determinant;
}

void printMatrixСoeffs(float *matrix[])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) 
        {
            printf("%-10.3f", matrix[i][j]);
        }
        std::cout << "\n";
    }
}

void transposeMatrix(float *m[], int row, int col)
{
    float curValue;
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++)
        {
            curValue = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = curValue;
        }
    }
}

float** invert (float* m[], float det)
{
    float** currMatrix = new float*[3];
    for (int i = 0; i < 3; i++) {
        currMatrix[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            currMatrix[i][j] = getAddition(m, i, j) / det;
        }
    }
    transposeMatrix(currMatrix, 3, 3);
    return currMatrix;
}

bool IsValidStr(std::string str) {
    static const std::regex r("^-{0,1}\\d+(\\.\\d+)?\\s+-{0,1}\\d+(\\.\\d+)?\\s+-{0,1}\\d+(\\.\\d+)?$");
    return regex_match(str, r);
}

void deleteMatrix (float* m[])
{
    for (int i = 0; i < 3; i++)
    {
        delete[] m[i];
    }
    delete[] m;
}

int main(int argc, char* argv[])
{
    auto arg = parseArgs(argc, argv);
    if (!argc) {
        std::cout << "Invalid argument count\n";
        std::cout << "the format of command line is: invert.exe <matrix.txt>\n";
        return 1;
    }
    std::stringstream strm;
    std::ifstream inputFile;
    inputFile.open(arg->c_str());
    if (!inputFile.is_open()) {
        std::cout << "Failed to open '" << arg->c_str() << "' for reading\n";
        return 1;
    }
    uint8_t strCounter = 0;
    std::string line;
    float** matrix = new float* [3];
    while (getline(inputFile, line))
    {
        if (!IsValidStr(line))
        {
            std::cout << "Not a number\n";
            return 1;
        }
        
        std::stringstream strm(line);
        matrix[strCounter] = new float[3];
        for (int j = 0; j < 3; j++) {
            strm >> matrix[strCounter][j];
        }
        strCounter++;
    }
    inputFile.close();
    if (strCounter != 3)
    {
        std::cout << "There can be only 3 lines in the input file\n";
        return 1;
    }
    
    float determinant = calcDeterminant(matrix);
    if (determinant == 0.0f) {
        std::cout << "This matrix is singular and non-invertible as the determinant is 0";
        return 0;
    }
    
    float **invertedMatrix = invert (matrix, determinant);
    printMatrixСoeffs(invertedMatrix);

    deleteMatrix(matrix);
    deleteMatrix(invertedMatrix);
 
    return 0;
}

