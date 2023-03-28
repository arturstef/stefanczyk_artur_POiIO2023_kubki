#pragma once
#include <iostream>
#include <vector>

class Tsubstance
{

	std::string name;
	double ro;

	public:
		Tsubstance(std::string name, double ro);
		std::string get_name();
		double get_ro();
};

extern std::vector<Tsubstance> substancje;
