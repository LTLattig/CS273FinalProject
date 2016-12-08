#pragma once
#ifndef PATIENT_
#define PATIENT_
struct Patient
{
	Patient(int clock) : arrivalTime(clock), treatmentTime(-1), startTreatmentTime(-1), endTreatmentTime(-1){}

	int treatmentTime;
	int arrivalTime;
	int startTreatmentTime;
	int endTreatmentTime;

};
#endif