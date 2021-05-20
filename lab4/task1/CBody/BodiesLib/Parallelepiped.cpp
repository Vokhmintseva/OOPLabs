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

std::string Parallelepiped::ToString(int level) const
{
	std::string baseInfo = Body::ToString(level);
	std::ostringstream info;
	std::string shift(level, (char)0x20);
	info << std::fixed << std::setprecision(2);
	info << shift << "Width: " << GetWidth() << "\n";
	info << shift << "Height: " << GetHeight() << "\n";
	info << shift << "Depth: " << GetDepth() << "\n";
	std::string infoStr = info.str();
	return std::move(baseInfo.append(std::move(infoStr)));
}