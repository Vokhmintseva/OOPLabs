#include "Complex.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <float.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream> 
#include <iomanip>

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
	if(fabs(m_real) < DBL_EPSILON && fabs(m_image) < DBL_EPSILON)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	return atan2(m_image, m_real);
}

Complex& Complex::operator +=(Complex const& rightOperand)
{
	m_real += rightOperand.m_real;
	m_image += rightOperand.m_image;
	return *this;
}

Complex& Complex::operator -=(Complex const& rightOperand)
{
	m_real -= rightOperand.m_real;
	m_image -= rightOperand.m_image;
	return *this;
}

Complex& Complex::operator *=(Complex const& rightOperand)
{
	double real = m_real * rightOperand.m_real - m_image * rightOperand.m_image;
	m_image = m_real * rightOperand.m_image + m_image * rightOperand.m_real;
	m_real = real;
	return *this;
}

Complex& Complex::operator /=(Complex const& rightOperand)
{
	if (fabs(rightOperand.m_real) < DBL_EPSILON && fabs(rightOperand.m_image) < DBL_EPSILON)
	{
		throw std::invalid_argument("not allowed to devide by 0");
	}
	const double& re = rightOperand.m_real;
	const double& im = rightOperand.m_image;
	double numeratorRe = m_real * re + m_image * im;
	double numeratorIm = m_real * im * (-1) + m_image * re;
	double denominator = re * re + im * im;
	m_real = numeratorRe / denominator;
	m_image = numeratorIm / denominator;
	return *this;
}

Complex const Complex::operator +() const
{
	return Complex(m_real, m_image);
}

Complex const Complex::operator -() const
{
	return Complex(m_real * (-1), m_image * (-1));
}

bool operator ==(Complex lhs, const Complex& rhs)
{
	return (fabs(lhs.Re() - rhs.Re()) < DBL_EPSILON) && (fabs(lhs.Im() - rhs.Im()) < DBL_EPSILON);
}

bool operator !=(Complex lhs, const Complex& rhs)
{
	return !(lhs == rhs);
}

Complex const operator +(Complex lhs, const Complex& rhs)
{
	return lhs += rhs;
}

Complex const operator -(Complex lhs, const Complex& rhs)
{
	return lhs -= rhs;
}

Complex const operator *(Complex lhs, const Complex& rhs)
{
	return lhs *= rhs;
}

Complex const operator /(Complex lhs, const Complex& rhs)
{
	return lhs /= rhs;
}

std::ostream& operator<<(std::ostream& stream, Complex const& complex)
{
	std::string sign;
	sign = complex.Im() >= 0 ? '+' : '-';
	stream << std::fixed << std::setprecision(1) << complex.Re() << sign << fabs(complex.Im()) << 'i';
	return stream;
}

std::istream& operator>>(std::istream& stream, Complex& complex)
{
	double re;
	double im;
	if ((stream >> re) && (stream >> im) && (stream.get() == 'i'))
	{
		Complex newComplex(re, im);
		complex = newComplex;
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}
	return stream;
}