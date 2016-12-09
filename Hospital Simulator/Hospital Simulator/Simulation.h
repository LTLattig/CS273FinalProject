#pragma once
#ifndef SIMULATION_
#define SIMULATION_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include "DoctorTreatment.h"
#include "NurseTreatment.h"
#include "WaitingRoomQueue.h"
#include "RandomValueGenerator.h"

class Simulation
{
private:
	int timeTotal;
	int clock;
	
	WaitingRoomQueue *waiting_room;
	trq_Doctor *doc_q;
	trq_Nurse *nurse_q;

	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) //don't make no sense, son. 
			throw std::invalid_argument("C'mon man don't be like that.\n We're running a serious business here.");
		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true)
			try {
			while (true) {
				std::cout << prompt;
				std::cin >> num;
				if (num >= low && num <= high) {
					//std::cout << "\n"; // Not sure why this is included in the airplane, might not need it here?
					return num;
				}
			}
		}
		catch (std::ios_base::failure) {
			std::cout << "Numbers we can use, now. It can't be that hard. We believe in you.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n'); //whaaaaaaat. Huh. numeric_limits returns the maximum finite
																	//value of the type in the angle brackets. That's honestly pretty neat. 
																	//Personal Note: this function shreds everything in the stream buffer until it clears the number of spaces
																	//up until the largest int. Otherwise, it stops when it hits a newline character. numeric_limits is found in the limits library. 
		}
	}

public:
	Simulation()
	{
		waiting_room = new WaitingRoomQueue();
		doc_q = new trq_Doctor(); 
		nurse_q = new trq_Nurse(); 
	}

	void enter_data()
	{
		std::cout << "Welcome once again to CS273ville!";
		std::cout << "This time rather than being an airport, we're a town with a population of 2000!\n";
		std::cout << "Strange how that works out.\n\n";

		int rate = read_int("Please let us know how bad you think the\n health conditions in CS273ville are (patients/hour): ", 1, 59);
		/*Also: user_sadism*/
		double patient_rate = rate / 60.0;

		std::cout << "Given that answer, you're going to help us set up a hospital that'll run for one full week.\n";

		int num_doctors = read_int("How many doctors are helping run this show? ", 1, 2017);
		int num_nurses = read_int("How about nurses? How many nurses do we have? ", 1, 2017);

		if (num_doctors + num_nurses > 2000)
			std::cout << "That's uh. Huh. You're aware your medical staff outnumbers townsfolk, right?";

		// sets arrival rate for the waiting room
		waiting_room->set_arrivalRate(patient_rate);
	}
	void run_simulation()
	{
		// Puts the simulation through the motions
		for (clock = 0; clock < 10080; clock++)
		{
			//update functions go here
		}
	}

	//I think we need a function to search through patient records. \
	Patient records would be generated in the DocQ and NurseQ, yeah? \
	Wait, no. It's in the WRQ. In any case: \
	void search_records() {}
};

#endif