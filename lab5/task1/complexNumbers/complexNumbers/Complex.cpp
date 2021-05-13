#include "Complex.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

Complex::Complex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double Complex::Re() const
{
	return m_real;
}

double Complex::Im() const
{
	return m_image;
}

double Complex::GetMagnitude() const
{
	return sqrt(pow(m_real, 2) + pow(m_image, 2));
}

double Complex::GetArgument() const
{
	if (m_real > 0.0)
	{
		return atan(m_image / m_real);
	}
	if (m_real < 0.0)
	{
		if (m_image < 0.0)
		{
			return atan(m_image / m_real) - M_PI;
		}
		else
		{
			return atan(m_image / m_real) + M_PI;
		}
	}
	return std::numeric_limits<double>::quiet_NaN();
}

Complex const Complex::operator +(Complex const& rightOperand) const
{
	return Complex(m_real + rightOperand.m_real, m_image + rightOperand.m_image);
}

Complex const Complex::operator *(Complex const& rightOperand) const
{
	return Complex(m_real * rightOperand.m_real - m_image * rightOperand.m_image,
		m_real * rightOperand.m_image + m_image * rightOperand.m_real);
}

Complex const Complex::operator *(double num) const
{
	return Complex(num * m_real, num * m_image);
}

Complex const operator -(Complex const& leftOperand, Complex const& rightOperand)
{
	return Complex(leftOperand.Re() - rightOperand.Re(), leftOperand.Im() - rightOperand.Im());
}

Complex const operator *(double num, Complex const& complexNum)
{
	return Complex(num * complexNum.Re(), num * complexNum.Im());
}
