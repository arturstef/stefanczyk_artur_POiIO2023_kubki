#include <iostream>
#include <vector>
#include "Tsubstance.hpp"
#include "Tcub.hpp"

using namespace std;

Tcub join(Tcub * cub1, Tcub * cub2);

int main()
{
	Tcub kubek1;
	kubek1.add("mleko",50);
	kubek1.add("woda",100);
	kubek1.add("mleko",50);
	kubek1.add_till_volume("oliwa",60);
	kubek1.add_till_mass("oliwa",70);
	cout << endl << "kubek1" << endl;
	kubek1.show();

	Tcub kubek2;
	kubek2.add("oliwa",50);
	kubek2.add("mleko",100);
	kubek2.add_till_mass("krem",30);
	cout << endl << "kubek2" << endl;
	kubek2.show();

	Tcub kubek3 = join(&kubek1, &kubek2);
	cout << endl << "kubek3 (kubek1 + kubek2)" << endl;
	kubek3.show();

	kubek2.join(&kubek3);
	cout << endl << "kubek2 (+kubek3)" << endl;
	kubek2.show()	;

	return 0;
}

Tcub join(Tcub * cub1, Tcub * cub2)
{
	Tcub new_cub;

	for (int i=0;i<cub1->get_substances().size();++i)
		new_cub.add(cub1->get_substances()[i],cub1->get_volumes()[i] * 1e6);	
	cub1->empty_cub();
	for (int i=0;i<cub2->get_substances().size();++i)
		new_cub.add(cub2->get_substances()[i],cub2->get_volumes()[i] * 1e6);
	cub2->empty_cub();
	
	return new_cub;
}
