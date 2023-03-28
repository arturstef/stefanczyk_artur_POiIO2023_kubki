#include "Tcub.hpp"

using namespace std;

std::vector<Tsubstance> Tcub::get_substances() { return substances; }
std::vector<double> Tcub::get_volumes() { return volumes; }

void Tcub::empty_cub()
{
	this->substances.clear();
	this->volumes.clear();
	this->masses_vec.clear();
	this->volumes_vec.clear();
	
	this->current_mass = 0;
	this->current_volume = 0;
	this->total_mass = 0;
	this->total_volume = 0;
}

void Tcub::join(Tcub * cub)
{
	for (int i=0;i<cub->get_substances().size();++i)	
		add(cub->get_substances()[i],cub->get_volumes()[i] * 1e6);
	cub->empty_cub();
}
	
void Tcub::add(Tsubstance substance, double volume_in_ml)
{
	this->current_volume += volume_in_ml * 1e6;
	this->current_mass += (floor(volume_in_ml) / 1e3) * substance.get_ro();	
	if (not this->check(substance.get_name(),volume_in_ml))
	{
		substances.push_back(substance);
		volumes.push_back(volume_in_ml / 1e6);
	}
}

void Tcub::add(std::string name, double volume_in_ml)
{
	int _id = get_substance_id(name);
	if (_id >= 0) this->add(substancje[_id], volume_in_ml);
}

void Tcub::add_till_volume(Tsubstance substance, double volume_percent)
{
	volume_percent = volume_percent / 100;
	double in_cub_volume = 0;
	int id = this->get_substance_id(substances, substance.get_name());

	if (id != -1) in_cub_volume = volumes[id] * 1e6;
	
	double total_volume = this->current_volume / 1e6;
	double new_substance_volume = this->get_proportion(volume_percent, total_volume, in_cub_volume);
	this->add(substance, new_substance_volume);
}

void Tcub::add_till_mass(Tsubstance substance, double mass_percent)
{
	mass_percent = mass_percent / 100;
	double in_cub_mass = 0;
	int id = this->get_substance_id(substances, substance.get_name());
	
	if (id != -1) in_cub_mass = 1e3 * volumes[id] * substance.get_ro();
	double total_mass = this->current_mass;
	double new_substance_mass = this->get_proportion(mass_percent, total_mass, in_cub_mass);
	double new_substance_volume = 1e3 * (new_substance_mass / substance.get_ro());
	this->add(substance, new_substance_volume);
}

void Tcub::add_till_volume(string substance, double volume_percent)
{
	volume_percent = volume_percent / 100;
	double in_cub_volume = 0;
	int id = this->get_substance_id(substance);

	if (id != -1) in_cub_volume = volumes[id] * 1e6;
	
	double total_volume = this->current_volume / 1e6;
	double new_substance_volume = this->get_proportion(volume_percent, total_volume, in_cub_volume);
	this->add(substance, new_substance_volume);
}

void Tcub::add_till_mass(string substance, double mass_percent)
{
	mass_percent = mass_percent / 100;
	double in_cub_mass = 0;
	int id = this->get_substance_id(substance);
	
	if (id != -1) in_cub_mass = 1e3 * volumes[id] * substancje[id].get_ro();
	double total_mass = this->current_mass;
	double new_substance_mass = this->get_proportion(mass_percent, total_mass, in_cub_mass);
	double new_substance_volume = 1e3 * (new_substance_mass / substancje[id].get_ro());
	this->add(substance, new_substance_volume);
}


double Tcub::get_proportion(double percent, double total, double total_in_cub)
{
	double proportion = (percent * total - total_in_cub) / (1 - percent);
	return proportion;
}

bool Tcub::check(std::string name, double volume_in_ml)
{
	bool is_in_cub = false;
	for(int i=0;i < substances.size();++i)
	{
		if (substances[i].get_name() == name)
		{
			this->volumes[i] = this->volumes[i] + volume_in_ml / 1e6;
			is_in_cub = true;
			break;				
		}
	}
	return is_in_cub;
}

void Tcub::show()
{
	this->get_total();	
	int count = substances.size();
	for (int i = 0; i < count; ++i)
	{
		double mass = substances[i].get_ro() * volumes[i] * 1e3;
		cout << substances[i].get_name() 
		<< " volume "<< volumes[i] * 1e6 << "ml"
		<< " mass " << mass << " g " 
		" mass ratio " << round(1e4 * this->masses_vec[i] / this->total_mass) / 1e2 << "%"
		" volume ratio " << round(1e4 * this->volumes_vec[i] / this->total_volume) / 1e2 << "%" << endl;
	}
	cout << endl;	
}
void Tcub::get_total()
{
	double total_mass = 0;
	double total_volume = 0;
	volumes_vec.clear();
	masses_vec.clear();
	for (int i = 0;i < substances.size(); ++i)
	{
		total_mass += volumes[i] * substances[i].get_ro(); 
		total_volume += volumes[i];
		volumes_vec.push_back(volumes[i]);
		masses_vec.push_back(volumes[i] * substances[i].get_ro());
	}
	this->total_mass = total_mass;
	this->total_volume = total_volume;
}

int Tcub::get_substance_id(string name)
{
	int count = substancje.size();
	int _id = -1;
	bool run = true;

	while (run)
	{
		_id += 1;
		string sub_name = substancje[_id].get_name();
		if (sub_name == name) run = false;

		if ((_id + 1 == count) and (run == true))
		{
			cout << "Nie znaleziono płynu " << name << endl;
			run = false;
			_id = -1;
		}		
	}
	return _id;
}

int Tcub::get_substance_id(std::vector<Tsubstance> given_substances, std::string name)
{
	int count = given_substances.size();
	int _id = -1;

	for (int i=0;i<count;++i)
	{
		if (given_substances[i].get_name() == name) { _id = i; }
	}

	return _id;
}
