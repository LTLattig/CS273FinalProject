#pragma once
#ifndef DOC_T_Q_
#define DOC_T_Q_
#include "TreatmentQueue.h"
#include "WaitingRoomQueue.h"
#include "Patient.h"
#include "RandomValueGenerator.h"
class trq_Doctor: public Treatment
{
private:
	unsigned int minTreatmentTime, maxTreatmentTime;
public:
	trq_Doctor(): minTreatmentTime(1), maxTreatmentTime(20) {}
};

#endif
