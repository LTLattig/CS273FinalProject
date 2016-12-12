#pragma once
#ifndef TREATMENT_Q_
#define TREATMENT_Q_
#include "WaitingRoomQueue.h"
#include "Patient.h"
#include "RandomValueGenerator.h"
#include <queue>
#include <list>
extern Random my_random;

class TreatmentQueue
{
protected:
	// contains the number of caregivers for the queue
	unsigned short int numberOfCaregivers;
	// takes Records multiset from WaitingRoomQueue
	unsigned int minTreatmentTime, maxTreatmentTime;
	WaitingRoomQueue *waitingQueue; // points to the 
	std::vector <Patient*> CurrentlyTreating;

public:
	TreatmentQueue() {}

	void set_waiting_room(WaitingRoomQueue *waiting_rm)
	{ this->waitingQueue = waiting_rm; }

	void update() //Polymorphim
	{
		std::cout << "Hmm... I'm not a trained proffesional but I'll wing it.\n";
	}
	
	

	
};

#endif