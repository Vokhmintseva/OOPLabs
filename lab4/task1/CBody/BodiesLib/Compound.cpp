#include "pch.h"
#include "Compound.h"

Compound::Compound()
	: Body(0, 0)
	, m_childs({})
{
}

Body::BodyType Compound::GetType()
{
	return Body::BodyType::Compound;
}

std::string Compound::GetName() const
{
	return "Compound";
}

bool Compound::AddChildBody(std::shared_ptr<Body> child)
{
	m_childs.push_back(child);
	return true;
}

double Compound::GetDensity() const
{
	double densityAvg = 0;
	double volumeTotal = GetVolume();
	if (volumeTotal)
	{
		densityAvg = GetMass() / volumeTotal;
	}
	return densityAvg;
}

double Compound::GetVolume() const
{
	double volumeTotal = 0;
	std::for_each(m_childs.rbegin(), m_childs.rend(), [&](auto& child) { volumeTotal += child->GetVolume(); });
	return volumeTotal;
}

double Compound::GetMass() const
{
	double massTotal = 0;
	std::for_each(m_childs.rbegin(), m_childs.rend(), [&](auto& child) { massTotal += child->GetMass(); });
	return massTotal;
}

std::string Compound::ToString() const
{
	std::string baseInfo = Body::ToString();
	std::string infoTotal = "\nBEGIN_BODIES_IN_COMPOUND:\n\n";
	std::for_each(m_childs.rbegin(), m_childs.rend(), [&](auto& child) { infoTotal += child->ToString() + '\n'; });
	infoTotal.append("END_BODIES_IN_COMPOUND\n");
	return baseInfo.append(std::move(infoTotal));
}