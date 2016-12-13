#pragma once
#ifndef WAITING_Q_
#define WAITING_Q_
#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <fstream>
#include <vector>
#include "Patient.h"
#include "RandomValueGenerator.h"
#include "TreatmentQueue.h"


extern Random my_random;

class WaitingRoomQueue
{
	friend class TreamentQueue;
private:
	double arrivalRate;
	unsigned int numberArrived;
	std::multiset<Patient> Records;
	std::vector<std::string> namePool;
	std::priority_queue<Patient*> highPriority;
	std::priority_queue<Patient*> lowPriority;
	
	long unsigned int totalWait;
public:
	
	WaitingRoomQueue() : totalWait(0),numberArrived(0){}
	void set_arrivalRate(double arrival_rate) {
		this->arrivalRate = arrival_rate;
		set_namePool();
	}
	/********************************//*
	Sets the name pool from the first
	name and surname test files 
	*//********************************/
	void set_namePool()
	{
		std::ifstream inFirst("residents_of_273ville.txt");
		std::ifstream inLast("surnames_of_273ville.txt");
		if(inFirst.fail())
		{
			std::cout << "Error: 'residents_of_273ville.txt' not found.\n";
			inFirst.close();
			exit(1);
		}
		if (inLast.fail())
		{
			std::cout << "Error: 'surnames_of_273ville.txt' not found.\n";
			inLast.close();
			exit(1);
		}
		std::string first_name;
		std::string last_name;
		while (getline(inFirst, first_name) && getline(inLast,last_name)) {
			namePool.push_back(last_name + ", " + first_name);
		}
		inFirst.close();
		inLast.close();
	}

	int get_totalWait() {
		return totalWait;
	}

	int get_numberArrived() {
		return numberArrived;
	}
	std::multiset<Patient> &getRecords()
	{
		return this->Records;
	}
	std::string getName(int i)
	{
		return namePool[i];
	}
	std::priority_queue<Patient*> &getHighPriorityQueue()
	{
		return this->highPriority;
	}
	std::priority_queue<Patient*> &getLowPriorityQueue()
	{
		return this->lowPriority;
	}
	/********************************//*
	Adds new patients to the highPriority
	and lowPriority prioirty Queues based 
	on the frequency of each severity.
	Chooses a random resident from the name
	pool.
	*//********************************/
	void update(int clock)
	{
		std::string name = getName(my_random.nextInt(namePool.size()-1));
		
		if(my_random.nextDouble() < arrivalRate) // if a patient arrives, assign them a random illness severity
		{
			double severityCheck = my_random.nextDouble(); 

			if (severityCheck >= .9)
				highPriority.push(new Patient(clock, my_random.nextInt(5) + 16,name)); //random value generator doesn't go up to n, needs to increase by 1
			else if (severityCheck >= .7)
				highPriority.push(new Patient(clock, my_random.nextInt(5) + 11,name));
			else
				lowPriority.push(new Patient(clock, my_random.nextInt(10) + 1,name));
			numberArrived++;
		}
	}
};
#endif