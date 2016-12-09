#pragma once
#ifndef NUR_T_Q_
#define NUR_T_Q_

#include "TreatmentQueue.h"
#include "WaitingRoomQueue.h"
#include "Patient.h"
#include "RandomValueGenerator.h"

class trq_Nurse : public Treatment
{
private: 
	unsigned int minTreatmentTime, maxTreatmentTime;
public:
	trq_Nurse(): minTreatmentTime (1), maxTreatmentTime(10) {};
};

#endif