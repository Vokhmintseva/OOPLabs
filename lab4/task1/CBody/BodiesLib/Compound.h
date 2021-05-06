#pragma once
#include <vector>
#include "Sphere.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Body.h"
#include "Compound.h"
#include "BodyNameResolver.h"

class Compound :
    public Body
{
public:    
    Compound();
    static Body::BodyType GetType();
    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    std::string GetName() const override;
    std::string ToString() const override;
    bool AddChildBody(std::shared_ptr<Body> child);
    
private:
    std::vector<std::shared_ptr<Body>> m_childs;
};

