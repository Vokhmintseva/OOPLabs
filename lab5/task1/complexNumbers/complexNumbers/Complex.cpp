#include "Complex.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <limits>
#include <stdexcept>
#include <iostream>
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
	if(fabs(m_real) < DBL_EPSILON)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	if (m_real > 0.0f)
	{
		return atan(m_image / m_real);
	}
	if (m_real < 0.0f)
	{
		if (m_image < 0.0f)
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

Complex const Complex::operator /(Complex const& rightOperand) const
{
	if (fabs(rightOperand.m_real) < DBL_EPSILON && fabs(rightOperand.m_image) < DBL_EPSILON)
	{
		throw std::invalid_argument("not allowed to devide by 0");
	}
	const double &re = rightOperand.m_real;
	const double &im = rightOperand.m_image;
	Complex numerator(m_real * re + m_image * im, m_real * im * (-1) + m_image * re);
	double denominator = re * re + im * im;
	return Complex(numerator.Re() / denominator, numerator.Im() / denominator);
}

Complex const Complex::operator +() const
{
	return Complex(m_real, m_image);
}

Complex const Complex::operator -() const
{
	return Complex(m_real * (-1), m_image * (-1));
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

bool Complex::operator ==(Complex const& rightOperand)
{
	return (fabs(m_real - rightOperand.Re()) < DBL_EPSILON) && (fabs(m_image - rightOperand.Im()) < DBL_EPSILON);
}

bool Complex::operator !=(Complex const& rightOperand)
{
	return (fabs(m_real - rightOperand.Re()) >= DBL_EPSILON) || (fabs(m_image - rightOperand.Im()) >= DBL_EPSILON);
}

Complex const operator -(Complex const& leftOperand, Complex const& rightOperand)
{
	return Complex(leftOperand.Re() - rightOperand.Re(), leftOperand.Im() - rightOperand.Im());
}

Complex const operator *(double num, Complex const& complexNum)
{
	return Complex(num * complexNum.Re(), num * complexNum.Im());
}

Complex const operator /(double num, Complex const& rightOperand)
{
	Complex numerator(num);
	return numerator / rightOperand;
}

bool operator ==(double num, Complex const& rightOperand)
{
	return (fabs(num - rightOperand.Re()) < DBL_EPSILON) && (fabs(rightOperand.Im()) < DBL_EPSILON);
}

bool operator !=(double num, Complex const& rightOperand)
{
	return (fabs(num - rightOperand.Re()) >= DBL_EPSILON) || (fabs(rightOperand.Im()) >= DBL_EPSILON);
}

std::ostream& operator<<(std::ostream& stream, Complex const& complex)
{
	std::string sign = "";
	if (complex.Im() >= 0)
	{
		sign = '+';
	}
	else
	{
		sign = '-';
	}
	const double& real = complex.Re();
	const double image = fabs(complex.Im());
	
	std::string realStr = "";
	if ((fabs(real) - (int)real) < 0.05)
	{
		realStr = std::to_string((int)real);
	}
	else
	{
		std::ostringstream strs;
		strs << std::fixed << std::setprecision(1) << real;
		realStr = strs.str();
	}

	std::string imageStr = "";
	if (image - (int)image < 0.05)
	{
		imageStr = std::to_string((int)image);
	}
	else
	{
		std::ostringstream strs2;
		strs2 << std::fixed << std::setprecision(1) << image;
		imageStr = strs2.str();
	}

	stream << realStr << sign << imageStr << 'i';
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