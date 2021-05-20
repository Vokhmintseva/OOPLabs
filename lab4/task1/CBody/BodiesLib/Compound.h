#pragma once
#include <vector>
#include "Sphere.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Body.h"
#include "Compound.h"

class Compound final:
    public Body,
    public std::enable_shared_from_this<Compound>
{
public:
    double GetDensity() const override;
    double GetVolume() const override;
    double GetMass() const override;
    std::string GetName() const override;
    std::string ToString(int level) const override;
    bool AddChildBody(std::shared_ptr<Body> childPtr);
private:
    std::weak_ptr<Body> GetParentPtr() const;
    void SetParentPtr(std::shared_ptr<Body> parentPtr);
    std::vector<std::shared_ptr<Body>> m_children;
    std::weak_ptr<Body> m_parent_ptr;
};