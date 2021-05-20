#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream> 
#include <iomanip>

class Complex
{
public:
	Complex(double real = 0, double image = 0);
	double Re()const;
	double Im()const;
	double GetMagnitude() const;
	double GetArgument() const;
	Complex const operator +(Complex const& rightOperand) const;
	Complex const operator *(Complex const& rightOperand) const;
	Complex const operator /(Complex const& rightOperand) const;
	Complex const operator +() const;
	Complex const operator -() const;
	Complex& operator +=(Complex const& rightOperand);
	Complex& operator -=(Complex const& rightOperand);
	Complex& operator *=(Complex const& rightOperand);
	Complex& operator /=(Complex const& rightOperand);
	bool operator ==(Complex const& rightOperand);
	bool operator !=(Complex const& rightOperand);
private:
	double m_real;
	double m_image;
};

Complex const operator -(Complex const& leftOperand, Complex const& rightOperand);
Complex const operator *(double num, Complex const& complexNum);
Complex const operator /(double num, Complex const& rightOperand);
bool operator ==(double num, Complex const& rightOperand);
bool operator !=(double num, Complex const& rightOperand);
std::ostream& operator<<(std::ostream& stream, Complex const& complex);
std::istream& operator>>(std::istream& stream, Complex& complex);