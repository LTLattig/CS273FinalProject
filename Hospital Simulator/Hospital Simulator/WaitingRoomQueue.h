#pragma once
#ifndef WAITING_Q_
#define WAITING_Q_
#include <iostream>
#include <string>
#include <set>
#include <queue>
#include "Patient.h"
#include "RandomValueGenerator.h"
extern Random myRandom;

class WaitingRoomQueue
{
	friend class Treament;
private:
	double arrivalRate;
	unsigned int numberTreated;
	std::multiset<Patient> Records;
	std::priority_queue<Patient*> myQueue; 
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

	void update(int clock)
	{
		if(myRandom.nextDouble() < arrivalRate) // if a patient arrives, assign them a random illness severity
		{
			int severityCheck = myRandom.nextDouble(); 
			
			if (severityCheck >= .9)
				myQueue.push(new Patient(clock, myRandom.nextInt(4) + 16));
			if (severityCheck >= .8)
				myQueue.push(new Patient(clock, myRandom.nextInt(4) + 11));
			else
				myQueue.push(new Patient(clock, myRandom.nextInt(9) + 1));
		}
	}
};
#endif