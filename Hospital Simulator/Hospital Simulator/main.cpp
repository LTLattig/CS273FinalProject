#include "Simulation.h"

Simulation lHospital;

int main()
{
	lHospital.enter_data();
	lHospital.run_simulation();
	lHospital.displayStats();
	std::cout << "\nEnter a name to search: ";
	std::string name;
	std::cin >> name;
	lHospital.search_records(name);
	return 0;
}