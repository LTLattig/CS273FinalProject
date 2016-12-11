#pragma once
#ifndef WAITING_Q_
#define WAITING_Q_
#include <iostream>
#include <string>
#include <set>
#include <queue>
#include "Patient.h"
#include "RandomValueGenerator.h"
#include "TreatmentQueue.h"

extern Random my_random;

class WaitingRoomQueue
{
	friend class TreamentQueue;
private:
	double arrivalRate;
	unsigned int numberTreated;
	std::multiset<Patient> Records;
	std::priority_queue<Patient*> highPriority;
	std::priority_queue<Patient*> lowPriority;
	long unsigned int totalWait;
public:
	
	WaitingRoomQueue() : totalWait(0),numberTreated(0){}
	void set_arrivalRate(double arrival_rate) {
		this->arrivalRate = arrival_rate;
	}

	int get_totalWait() {
		return totalWait;
	}

	int get_numberTreated() {
		return numberTreated;
	}
	std::multiset<Patient> &getRecords()
	{
		return this->Records;
	}
	std::priority_queue<Patient*> &getHighPriorityQueue()
	{
		return this->highPriority;
	}
	std::priority_queue<Patient*> &getLowPriorityQueue()
	{
		return this->lowPriority;
	}
	void update(int clock)
	{
		std::string name = "temp";
		if(my_random.nextDouble() < arrivalRate) // if a patient arrives, assign them a random illness severity
		{
			double severityCheck = my_random.nextDouble(); 
			
			if (severityCheck >= .9)
				highPriority.push(new Patient(clock, my_random.nextInt(4) + 16,name));
			if (severityCheck >= .8)
				highPriority.push(new Patient(clock, my_random.nextInt(4) + 11,name));
			else
				lowPriority.push(new Patient(clock, my_random.nextInt(9) + 1,name));
		}
	}
};
#endif