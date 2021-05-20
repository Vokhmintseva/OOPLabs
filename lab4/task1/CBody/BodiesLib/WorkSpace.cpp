#include "pch.h"
#include "WorkSpace.h"

using namespace std::placeholders;

WorkSpace::WorkSpace(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "sphere", bind(&WorkSpace::AddSphere, this, std::placeholders::_1) },
		  { "parallelepiped", bind(&WorkSpace::AddParallelepiped, this, std::placeholders::_1) },
		  { "cone", bind(&WorkSpace::AddCone, this, std::placeholders::_1) },
		  { "cylinder", bind(&WorkSpace::AddCylinder, this, std::placeholders::_1) },
		  { "compound", bind(&WorkSpace::AddCompound, this, std::placeholders::_1) },
		  { "endCompound", bind(&WorkSpace::RemoveLastCompoundPtr, this, std::placeholders::_1) },
		  { "help", bind(&WorkSpace::Info, this, std::placeholders::_1) }
		})
{
}

bool WorkSpace::Info(std::istream& args)
{
	m_output << "sphere <density> <radius>\n";
	m_output << "cylinder <density> <base_radius> <height>\n";
	m_output << "parallelepiped <density> <width> <height> <depth>\n";
	m_output << "cone <density> <base_radius> <height>\n\n";
	m_output << "compound\n";
	m_output << "sphere <density> <radius>\n";
	m_output << "cylinder <density> <base_radius> <height>\n";
	m_output << "endCompound\n";
	return true;
}

bool WorkSpace::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

std::optional<std::vector<double>> ParseArgs(std::istream& args)
{
	std::string str;
	getline(args, str);
	std::istringstream strm(str);
	std::vector<double> arr;
	double num;
	while (strm >> num)
	{
		if (num <= 0.0)
		{
			return std::nullopt;
		}
		arr.push_back(num);
	}
	if (!strm.eof())
	{
		return std::nullopt;
	}
	return arr;
}

void WorkSpace::PrintBodiesInfo()
{
	int level = 0;
	m_output << std::accumulate(m_bodies.begin(), m_bodies.end(), std::string{},
		[level](std::string infoTotal, const std::shared_ptr<Body>& body) { return infoTotal += body->ToString(level) + '\n'; });
}

void WorkSpace::PrintMaxMassBody() const
{
	auto CompareWeight = [](const std::shared_ptr<Body>& body1, const std::shared_ptr<Body>& body2)
	{
		return body1->GetMass() < body2->GetMass();
	};
	auto maxWeightBody = std::max_element(m_bodies.cbegin(), m_bodies.cend(), CompareWeight);
	m_output << "THE BODY WITH THE BIGGEST MASS IS:\n" << (*maxWeightBody)->ToString(0);
}

void WorkSpace::PrintBodyWithLeastWeightInWater() const
{
	const double gravity(9.80665);
	const double waterDensity(1000);
	auto CompareWeigtInWater = [gravity, waterDensity](const std::shared_ptr<Body>& body1, const std::shared_ptr<Body>& body2)
	{
		return (body1->GetDensity() - waterDensity) * body1->GetMass() * gravity < (body2->GetDensity() - waterDensity)* body2->GetMass()* gravity;
	};
	auto body = std::min_element(m_bodies.cbegin(), m_bodies.cend(), CompareWeigtInWater);
	m_output << "THE BODY WITH THE LEAST WEIGHT IN WATER IS:\n" << (*body)->ToString(0);
}

bool WorkSpace::AddSphere(std::istream& input)
{
	auto args = ParseArgs(input);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 2)
	{
		return false;
	}
	auto sphere = std::make_shared<Sphere>(arguments[0], arguments[1]);
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(std::move(sphere));
	}
	else
	{
		std::weak_ptr<Compound> it = m_compounds.back();
		it.lock()->AddChildBody(sphere);
	}
	return true;
}

bool WorkSpace::AddParallelepiped(std::istream& input)
{
	auto args = ParseArgs(input);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 4)
	{
		return false;
	}
	auto parallelepiped = std::make_shared<Parallelepiped>(arguments[0], arguments[1], arguments[2], arguments[3]);
	if (m_compounds.empty())
	{
		m_bodies.push_back(parallelepiped);
	}
	else
	{
		std::weak_ptr<Compound> it = m_compounds.back();
		it.lock()->AddChildBody(std::move(parallelepiped));
	}
	return true;
}

bool WorkSpace::AddCone(std::istream& input)
{
	auto args = ParseArgs(input);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 3)
	{
		return false;
	}
	auto cone = std::make_shared<Cone>(arguments[0], arguments[1], arguments[2]);
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(std::move(cone));
	}
	else
	{
		std::weak_ptr<Compound> it = m_compounds.back();
		it.lock()->AddChildBody(cone);
	}
	return true;
}

bool WorkSpace::AddCylinder(std::istream& input)
{
	auto args = ParseArgs(input);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 3)
	{
		return false;
	}
	auto cylinder = std::make_shared<Cylinder>(arguments[0], arguments[1], arguments[2]);
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(std::move(cylinder));
	}
	else
	{
		std::weak_ptr<Compound> it = m_compounds.back();
		it.lock()->AddChildBody(cylinder);
	}
	return true;
}

bool WorkSpace::AddCompound(std::istream& input)
{
	auto args = ParseArgs(input);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (!arguments.empty())
	{
		return false;
	}
	auto compound = std::make_shared<Compound>();
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(compound);
	}
	else
	{
		std::weak_ptr<Compound> it = m_compounds.back();
		it.lock()->AddChildBody(compound);
	}
	m_compounds.emplace_back(compound);
	return true;
}

bool WorkSpace::RemoveLastCompoundPtr(std::istream& input)
{
	if (!input.eof())
	{
		return false;
	}
	if (m_compounds.empty())
	{
		return false;
	}
	m_compounds.pop_back();
	return true;
}