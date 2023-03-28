#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "Tsubstance.hpp"

class Tcub
{
	std::vector<Tsubstance> substances;
	std::vector<double> volumes;
	std::vector<double> masses_vec;
	std::vector<double> volumes_vec;

	double current_mass = 0;
	double current_volume = 0;

	double total_mass = 0;
	double total_volume = 0;

	public:
		void add(Tsubstance substance, double volume_in_ml);
		void add(std::string name, double volume_in_ml);
		void add_till_volume(Tsubstance substance,double volume_percent);
		void add_till_mass(Tsubstance substance,double mass_percent);
		void add_till_volume(std::string substance,double volume_percent);
		void add_till_mass(std::string substance,double mass_percent);
		void empty_cub();
		void show();
		void get_total();
		std::vector<Tsubstance> get_substances();
		std::vector<double> get_volumes();
		void join(Tcub * cub);
	private:
		int get_substance_id(std::string name);
		int get_substance_id(std::vector<Tsubstance> given_substances, std::string name);
		bool check(std::string name, double volume_in_ml);
		double get_proportion(double percent, double total, double total_in_cub);
};
