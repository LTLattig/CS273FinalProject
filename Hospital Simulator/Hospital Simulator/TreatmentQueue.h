#pragma once
#ifndef TREATMENT_Q_
#define TREATMENT_Q_
#include "WaitingRoomQueue.h"
#include "Patient.h"
#include "RandomValueGenerator.h"
#include <queue>
extern Random myRandom;

class Treatment
{
protected:
	// contains the number of caregivers for the queue
	unsigned short int numberOfCaregivers;
	// takes Records multiset from WaitingRoomQueue
	unsigned int minTreatmentTime, maxTreatmentTime;
	WaitingRoomQueue *waitingQueue; 
	std::queue<Patient*> lowPriority;
	std::queue<Patient*> highPriority; // wait hold on I thought we were using priority queues for this. \\
	The way this is set up, it looks like the high priority queue is first come-first serve, which seems silly. 
public:
	Treatment() {}

	void set_waiting_room(WaitingRoomQueue *waiting_rm)
	{ this->waitingQueue = waiting_rm; }

	void seperatePatients()
	{
		waitingQueue->myQueue.empty(); // Works if you move WR myQ into public, but we probably don't want that. 
	}


	
};

#endif