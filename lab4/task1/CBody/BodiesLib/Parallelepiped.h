#pragma once
#include "SolidBody.h"

class Parallelepiped :
    public SolidBody
{
public:
    Parallelepiped(double density, double width, double height, double depth);
    std::string GetName() const override;
    std::string ToString(int level) const override;
    double GetVolume() const override;
    double GetWidth() const;
    double GetHeight() const;
    double GetDepth() const;
private:
    double m_width;
    double m_height;
    double m_depth;
};

