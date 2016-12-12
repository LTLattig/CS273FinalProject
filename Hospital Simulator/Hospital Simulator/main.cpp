/*CS-273 Final Project
 * Hopital Simulation
 * Bao Tran & Luke Lattig
 * Whitworth Univeristy
 * 12/11/2016
 */

#include "Simulation.h"

Simulation lHospital;

int main()
{
	lHospital.enter_data();
	lHospital.run_simulation();
	lHospital.displayMenu();

	return 0;
}