#pragma once
#include "Body.h"
class Cone :
    public Body
{
public:
    Cone(double density, double volume, double height);
    static Body::BodyType GetType();
    double GetHeight() const;
    double GetBaseRadius() const;
    std::string GetName() const override;
    std::string ToString() const override;
private:
    double m_height;
    double m_baseRadius;
};

