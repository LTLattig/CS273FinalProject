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
	unsigned int numberArrived;
	std::multiset<Patient> Records;
	std::priority_queue<Patient*> highPriority;
	std::priority_queue<Patient*> lowPriority;
	long unsigned int totalWait;
public:
	
	WaitingRoomQueue() : totalWait(0),numberArrived(0){}
	void set_arrivalRate(double arrival_rate) {
		this->arrivalRate = arrival_rate;
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