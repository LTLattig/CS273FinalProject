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
	unsigned short int numberOfCaregivers;
	// takes Records multiset from WaitingRoomQueue
	unsigned int minTreatmentTime, maxTreatmentTime;
	WaitingRoomQueue *waitingQueue;
	std::queue<Patient*> lowPriority;
	std::queue<Patient*> highPriority;
public:
	Treatment(WaitingRoomQueue *waitngRoomQueue)  { this->waitingQueue = waitngRoomQueue; }

	void seperatePatients()
	{
		(waitingQueue->myQueue.empty();
		
	}



};

#endif