#pragma once
#ifndef SIMULATION_
#define SIMULATION_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <iomanip>
#include "DoctorTreatment.h"
#include "NurseTreatment.h"
#include "WaitingRoomQueue.h"
#include "RandomValueGenerator.h"
Random my_random;
class Simulation
{
private:
	int timeTotal;
	int clock;
	
	WaitingRoomQueue *waiting_room;
	trq_Doctor *doc_q;
	trq_Nurse *nurse_q;
	/********************************//*
	Displays Prompt and checks validity
	of the input
	*//********************************/
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

	}
	/********************************//*
	Displays the menu after the 
	simulation. Will loop until the 
	user quits the program
	*//********************************/
	void displayMenu()
	{
		while (true) {
			std::cin.ignore();
		std::cout << "\nWhat would you like to do?\n";
		int option = read_int("1) Display Statistics\n2) Display all patients in records\n3) Search a name\n4) Quit\n", 1, 4);
		std::string name;
		/*****Menu Options*****/
		if (option == 1)
			displayStats();
		else if (option == 2)
			displayAllPatients();
		else if (option == 3)
		{
			std::cout << "Enter the name you would like to search for: ";
			std::cin.ignore();
			getline(std::cin, name);
			search_records(name);
		}
		else if (option == 4)
		{
			std::cout << "Peace Out Girl Scouts!\n";
			return;
		}
		/*****Menu Options*****/
		}
	}
	/********************************//*
	Prompts user with initial data to
	begin simulation.
	Data:
		# of Doctors
		# of Nurses
		Patient Arrival Rate
	Creates Doctor and nurse classes
	*//********************************/
	void enter_data()
	{
		std::cout << "Welcome once again to CS273ville!";
		std::cout << "This time rather than being an airport, we're a town with a population of 2000!\n";
		std::cout << "Strange how that works out.\n\n";

		int rate = read_int("Please let us know how bad you think the\nhealth conditions in CS273ville are (patients/hour): ", 1, 59);
		/*Also: user_sadism*/
		double patient_rate = rate / 60.0;

		std::cout << "Given that answer, you're going to help us set up a hospital that'll run for one full week.\n";
	

		// Create the classes for doctor and nurse
		int num_doctors = read_int("How many doctors are helping run this show? ", 1, 100);
		doc_q = new trq_Doctor(num_doctors);
		int num_nurses = read_int("How about nurses? How many nurses do we have? ", 1, 100);
		nurse_q = new trq_Nurse(num_nurses);

	

		

		// sets arrival rate for the waiting room
		waiting_room->set_arrivalRate(patient_rate);
	}
	/********************************//*
	Runs simulation and initializes
	the clock variable used throughout
	simulation. Iterates clock.
	*//********************************/
	void run_simulation()
	{
		doc_q->set_waiting_room(waiting_room);
		nurse_q->set_waiting_room(waiting_room);
		// Puts the simulation through the motions
		for (clock = 0; clock < 10080; clock++)
		{
			//update functions go here
			waiting_room->update(clock);
			nurse_q->update(clock);
			doc_q->update(clock);
		}
	}

	
	/********************************//*
	Finds the record of a patient
	if their treatment has been completed.
	Displays all visits of the patient
	with the corresponding severity
	and treatment time for that visit.
	*//********************************/
	void search_records(std::string name)
	{
		auto search = waiting_room->getRecords().find(Patient(name));
		if (search != waiting_room->getRecords().end())
		{
			std::cout << name << std::endl;
			std::cout << "*********************" << std::endl;
			std::cout << "Visits - " << waiting_room->getRecords().count(Patient(name)) << std::endl;

			int visitTimes = 1;
			for (auto it = waiting_room->getRecords().lower_bound(Patient(name)); it != waiting_room->getRecords().upper_bound(Patient(name)); ++it)
			{
				std::cout << "\t\t Visit(" << visitTimes << ") \t Severity : " << it->severity << " \t Treatment Time : " << it->treatmentTime << std::endl;
				visitTimes++;
			}
			
		}
		std::cout << "Press Enter to continue:\n";
		
	}
	/********************************//*
	Displays all Patients in the Records
	multiset. Does not repeat if Patient
	is in records more than once.
	*//********************************/
	void displayAllPatients()
	{
		auto it = waiting_room->getRecords().begin();
		std::string prevName = " ";
		int newline = 0;
		do 
		{
			//Only displays if it is a new patient that hasn't been displayed.
			
			if (it->name != prevName)
			{
				std::cout << std::setw(21) << std::left << it->name;
				newline++;
				if (newline % 8 == 0)
					std::cout << std::endl;
			}
	
			//Used to indicate if it is a new Patient
			prevName = it->name;
			++it;

		} while (it != waiting_room->getRecords().end());
	}
	/********************************//*
	Displays percentage stats of patient
	severity for all patients that have been
	treated (excludes Patients still being
	treated when simulation ends or those 
	who are still waiting)
	
	Displays patient count that have finished
	their treatment.

	Displays average wait time of patients
	(calculated by those who have finished
	treatment; Excludes currenlty being 
	treated when simulation ends and those
	still in waiting room queue)
	*//********************************/
	void displayStats()
	{
		double totalVisitsInRecords = waiting_room->getRecords().size(); // Displays all visits (that have been treated)
		double lessthan10 = 0, greaterthan15 = 0, between11and15 = 0;
		double averageWait = 0;
		//Calculates percentages of severity stat
		auto it = waiting_room->getRecords().begin();
		while (it != waiting_room->getRecords().end())
		{
			averageWait += it->startTreatmentTime - it->arrivalTime;
			if (it->severity <= 10)
				lessthan10++;
			else if (it->severity > 15)
				greaterthan15++;
			else
				between11and15++;
			++it;
		}
		std::cout << "\n\tPercentage of Patients treated within timeframe: " << totalVisitsInRecords / waiting_room->get_numberArrived() * 100 << "%\n";
		std::cout << "\n\tSeverity less than 10: " << lessthan10 / totalVisitsInRecords * 100 << "%\t\tSeverity Between 11 and 15: " << between11and15 / totalVisitsInRecords * 100 << "%\t\tSeverity over 15: " << greaterthan15 / totalVisitsInRecords * 100 << std::endl;
		std::cout << "\n\tAverage Wait Time of Treated Patients: " << averageWait / totalVisitsInRecords << " minutes\n";
	}
};

#endif