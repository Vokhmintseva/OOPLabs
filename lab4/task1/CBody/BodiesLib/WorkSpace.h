#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "Body.h"
#include "Compound.h"

class WorkSpace
{
public:	
	WorkSpace(std::istream& input, std::ostream& output);
	bool HandleCommand();
	void PrintBodiesInfo();
	void PrintMaxMassBody() const;
	void PrintBodyWithLeastWeightInWater() const;

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	
	bool AddSphere(std::istream& args);
	bool AddParallelepiped(std::istream& args);
	bool AddCone(std::istream& args);
	bool AddCylinder(std::istream& args);
	bool AddCompound(std::istream& args);
	bool RemoveLastCompoundPtr(std::istream& args);
	bool Info(std::istream& args);
	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::shared_ptr<Body>> m_bodies;
	std::vector<std::shared_ptr<Compound>> m_compounds;
};

