#pragma once
#include <iostream>

class Complex
{
public:
	Complex(double real = 0, double image = 0);
	double Re()const;
	double Im()const;
	double GetMagnitude() const;
	double GetArgument() const;
	Complex& operator +=(Complex const& rightOperand);
	Complex& operator -=(Complex const& rightOperand);
	Complex& operator *=(Complex const& rightOperand);
	Complex& operator /=(Complex const& rightOperand);
	Complex const operator +() const;
	Complex const operator -() const;
private:
	double m_real;
	double m_image;
};

Complex const operator +(Complex lhs, const Complex& rhs);
Complex const operator -(Complex lhs, const Complex& rhs);
Complex const operator *(Complex lhs, const Complex& rhs);
Complex const operator /(Complex lhs, const Complex& rhs);

bool operator ==(Complex lhs, const Complex& rhs);
bool operator !=(Complex lhs, const Complex& rhs);
std::ostream& operator<<(std::ostream& stream, Complex const& complex);
std::istream& operator>>(std::istream& stream, Complex& complex);