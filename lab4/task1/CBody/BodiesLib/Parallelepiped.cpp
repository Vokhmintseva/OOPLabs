#include "pch.h"
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(double density, double volume, double width, double height)
	: Body(density, volume)
	, m_width(width)
	, m_height(height)
	, m_depth(volume / width / height)
{}

Body::BodyType Parallelepiped::GetType()
{
	return Body::BodyType::Parallelepiped;
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

std::string Parallelepiped::ToString() const
{
	std::string baseInfo = Body::ToString();
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << "Width: " << GetWidth() << "\n";
	info << "Height: " << GetHeight() << "\n";
	info << "Depth: " << GetDepth() << "\n";
	std::string infoStr = info.str();
	return std::move(baseInfo.append(std::move(infoStr)));
}