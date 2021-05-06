#include "pch.h"
#include "BodyNameResolver.h"

std::string BodyNameResolver::ResolveName(Body::BodyType bodyType)
{
	switch (bodyType)
	{
	case Body::BodyType::Compound:
		return "Compound";
	case Body::BodyType::Sphere:
		return "Sphere";
	case Body::BodyType::Cone:
		return "Cone";
	case Body::BodyType::Cylinder:
		return "Cylinder";
	case Body::BodyType::Parallelepiped:
		return "Parallelepiped";
	default:
		return "";
	}
}