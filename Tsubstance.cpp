#include "Tsubstance.hpp"

using namespace std;

Tsubstance::Tsubstance(string name, double ro)
{
	this->name = name;
	this->ro = ro;
}

string Tsubstance::get_name()
{
	return this->name;
}


double Tsubstance::get_ro()
{
	return this->ro;
}

vector<Tsubstance> substancje =
{
	Tsubstance("woda",997.8),
	Tsubstance("mleko",1030.0),
	Tsubstance("oliwa",920.0),
	Tsubstance("krem",1050.0)
};
