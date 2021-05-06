#pragma once
#include <string>
#include <iostream>
#include "Sphere.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Body.h"
#include "Compound.h"
#include "BodyNameResolver.h"

struct BodyInfoBuilder
{
    [[nodiscard]] std::string operator()(const Sphere& sphere)
    {
        std::string info = BodyNameResolver::ResolveName(Body::BodyType::Sphere) + ":\n" + sphere.ToString();
        return std::move(info);
    }

    [[nodiscard]] std::string operator()(const Cylinder& cylinder)
    {
        std::string info = BodyNameResolver::ResolveName(Body::BodyType::Cylinder) + ":\n" + cylinder.ToString();
        return std::move(info);
    }

    [[nodiscard]] std::string operator()(const Parallelepiped& parallelepiped)
    {
        std::string info = BodyNameResolver::ResolveName(Body::BodyType::Parallelepiped) + ":\n" + parallelepiped.ToString();
        return std::move(info);
    }

    [[nodiscard]] std::string operator()(const Cone& cone)
    {
        std::string info = BodyNameResolver::ResolveName(Body::BodyType::Cone) + ":\n" + cone.ToString();
        return std::move(info);
    }

    [[nodiscard]] std::string operator()(const Compound& compound)
    {
        std::string info = BodyNameResolver::ResolveName(Body::BodyType::Compound) + ":\n" + compound.ToString();
        return std::move(info);
    }
};
