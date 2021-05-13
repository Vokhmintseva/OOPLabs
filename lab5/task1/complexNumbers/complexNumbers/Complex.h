#pragma once
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
	Complex const operator *(double num) const;
private:
	double m_real;
	double m_image;
};

Complex const operator -(Complex const& leftOperand, Complex const& rightOperand);
Complex const operator *(double num, Complex const& complexNum);

