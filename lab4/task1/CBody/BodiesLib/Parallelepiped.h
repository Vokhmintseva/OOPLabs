#pragma once
#include "Body.h"

class Parallelepiped :
    public Body
{
public:
    Parallelepiped(double density, double volume, double width, double height);
    static Body::BodyType GetType();
    double GetWidth() const;
    double GetHeight() const;
    double GetDepth() const;
    std::string GetName() const override;
    std::string ToString() const override;
private:
    double m_width;
    double m_height;
    double m_depth;
};

