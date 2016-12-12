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


	/********************************//*
	Process for simulation updates
	*//********************************/
	void update(int clock)
	{
		/* If the vector of curretly treated patients is not empty, check if there are any patients ready to be release from the hospital*/
		if (!CurrentlyTreating.empty())
		{
		
			for (int i = 0; i < CurrentlyTreating.size();)
			{
				Patient *patient = CurrentlyTreating[i];
				//Checks if the patient is done with their treatment
				if ((clock - patient->startTreatmentTime) > patient->treatmentTime)
				{
					//Puts the patient into the records, deletes them from the currently treated queue
					patient->endTreatmentTime = clock;
					waitingQueue->getRecords().insert(*patient);
					CurrentlyTreating.erase(CurrentlyTreating.begin() + i);
				}
				else
					++i;// iterate only when a patient is not deleted. Checks same index twice when patient is removed.

			}
		}
		// Checks if their is an available doctor to treat a patient
		if (CurrentlyTreating.size() < numberOfCaregivers)
		{
			for (int i = CurrentlyTreating.size(); i <= numberOfCaregivers; i++)
			{
				//Can only serve low priority patients
			if (!waitingQueue->getLowPriorityQueue().empty())
				{
					Patient *patient = waitingQueue->getLowPriorityQueue().top();
					patient->startTreatmentTime = clock;
					patient->treatmentTime = my_random.nextInt((maxTreatmentTime - minTreatmentTime))+1;
					CurrentlyTreating.push_back(patient);
					waitingQueue->getLowPriorityQueue().pop();
					i = CurrentlyTreating.size();
				}
			}
		}
	}
};

#endif