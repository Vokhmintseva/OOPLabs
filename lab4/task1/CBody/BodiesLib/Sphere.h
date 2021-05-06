#pragma once
#include "Body.h"

class Sphere :
    public Body
{
public:
    Sphere(double density, double volume);
    static Body::BodyType GetType();
    double GetRadius() const;
    std::string GetName() const override;
    std::string ToString() const override;
private:
    double m_radius;
};

