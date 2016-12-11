#pragma once
#ifndef NUR_T_Q_
#define NUR_T_Q_

#include "TreatmentQueue.h"
#include "WaitingRoomQueue.h"
#include "Patient.h"
#include "RandomValueGenerator.h"

class trq_Nurse : public TreatmentQueue
{
private: 
	unsigned int minTreatmentTime, maxTreatmentTime;
public:
	trq_Nurse(unsigned short int numberOfNurses): minTreatmentTime (1), maxTreatmentTime(10)
	{
		numberOfCaregivers = numberOfNurses;
	}




	void update(int clock)
	{

		if (!CurrentlyTreating.empty())
		{
			std::vector<Patient*>::iterator it = CurrentlyTreating.begin();
			while (it != CurrentlyTreating.end())
			{
				Patient *patient = *it;
				if ((clock - patient->startTreatmentTime) > patient->treatmentTime)
				{
					patient->endTreatmentTime = clock;
					waitingQueue->getRecords().insert(*patient);
					it = CurrentlyTreating.erase(it);
				}
				else
					++it;
			}
		}
		if (CurrentlyTreating.size() < numberOfCaregivers)
		{
			for (int i = CurrentlyTreating.size(); i <= numberOfCaregivers; i++)
			{
			if (!waitingQueue->getLowPriorityQueue().empty())
				{
					Patient *patient = waitingQueue->getLowPriorityQueue().top();
					patient->startTreatmentTime = clock;
					patient->treatmentTime = my_random.nextInt((maxTreatmentTime - minTreatmentTime));
					CurrentlyTreating.push_back(patient);
					waitingQueue->getLowPriorityQueue().pop();
					i = CurrentlyTreating.size();
				}
			}
		}
	}
};

#endif