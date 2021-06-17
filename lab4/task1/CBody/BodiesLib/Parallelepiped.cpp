#include "pch.h"
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(double density, double width, double height, double depth)
	: SolidBody(density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

std::string Parallelepiped::GetName() const
{
	return "Parallelepiped";
}

double Parallelepiped::GetWidth() const
{
	return m_width;
}

double Parallelepiped::GetHeight() const
{
	return m_height;
}

double Parallelepiped::GetDepth() const
{
	return m_depth;
}

double Parallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

void Parallelepiped::AppendProperties(std::ostream& strm, int level) const
{
	std::string shift(level, (char)0x20);
	strm << shift << "Width: " << GetWidth() << "\n";
	strm << shift << "Height: " << GetHeight() << "\n";
	strm << shift << "Depth: " << GetDepth() << "\n";
}
