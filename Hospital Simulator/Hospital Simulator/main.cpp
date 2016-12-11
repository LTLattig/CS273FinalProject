#include "Simulation.h"

Simulation lHospital;

int main()
{
	lHospital.enter_data();
	lHospital.run_simulation();
	std::cout << "enter a name to search: ";
	std::string name;
	getline(std::cin, name);
	lHospital.search_records(name);
	return 0;
}