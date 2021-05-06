#pragma once
#include "Body.h"

class BodyNameResolver
{
public:	
	static std::string ResolveName(Body::BodyType bodyType);
};
