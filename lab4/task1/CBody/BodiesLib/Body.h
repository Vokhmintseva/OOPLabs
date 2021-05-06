#pragma once

class Body
{
public:
	explicit Body(double density, double volume);
	
	enum class BodyType {Sphere, Parallelepiped, Cone, Cylinder, Compound};
	virtual double GetDensity() const;
	virtual double GetVolume() const;
	virtual double GetMass() const;
	virtual std::string ToString() const;
	virtual std::string GetName() const;
	virtual ~Body() = default;

private:
	double m_density;
	double m_volume;
	double m_mass;
};

