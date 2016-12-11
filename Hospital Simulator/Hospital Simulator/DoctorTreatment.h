#pragma once
#ifndef DOC_T_Q_
#define DOC_T_Q_
#include "TreatmentQueue.h"
#include "WaitingRoomQueue.h"
#include "Patient.h"
#include "RandomValueGenerator.h"
class trq_Doctor: public TreatmentQueue
{
private:
	unsigned int minTreatmentTime, maxTreatmentTime;
public:
	trq_Doctor(unsigned short int numberOfDoctors): minTreatmentTime(1), maxTreatmentTime(20)
	{
		numberOfCaregivers = numberOfDoctors;
	}

	 void update(int clock) 
	{

		if (!CurrentlyTreating.empty())
		{
			for (int i = 0; i < CurrentlyTreating.size();)
			{
				Patient *patient = CurrentlyTreating[i];
				if ((clock - patient->startTreatmentTime) > patient->treatmentTime)
				{
					patient->endTreatmentTime = clock;
					waitingQueue->getRecords().insert(*patient);
					CurrentlyTreating.erase(CurrentlyTreating.begin() + i);
				}
				else
					++i;
			}
		}
		if (CurrentlyTreating.size()<numberOfCaregivers)
		{
			for (int i = CurrentlyTreating.size(); i <= numberOfCaregivers;i++)
			{
				if (!this->waitingQueue->getHighPriorityQueue().empty())				{
					Patient *patient = this->waitingQueue->getHighPriorityQueue().top();
					patient->startTreatmentTime = clock;
					patient->treatmentTime = my_random.nextInt((maxTreatmentTime+1 - minTreatmentTime))+1;
					CurrentlyTreating.push_back(patient);
					this->waitingQueue->getHighPriorityQueue().pop();
					i = CurrentlyTreating.size();
				}
				else if (!this->waitingQueue->getLowPriorityQueue().empty())
				{
					Patient *patient = this->waitingQueue->getLowPriorityQueue().top();
					patient->startTreatmentTime = clock;
					patient->treatmentTime = my_random.nextInt((maxTreatmentTime+1 - minTreatmentTime))+1;
					CurrentlyTreating.push_back(patient);
					this->waitingQueue->getLowPriorityQueue().pop();
					i = CurrentlyTreating.size();
				}
			}
		}

	}
};

#endif
