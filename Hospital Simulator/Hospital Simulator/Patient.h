#pragma once
#ifndef PATIENT_
#define PATIENT_
struct Patient
{
	Patient(int clock, int severity) : arrivalTime(clock), treatmentTime(-1), startTreatmentTime(-1), endTreatmentTime(-1){}

	int severity;
	int treatmentTime;
	int arrivalTime;
	int startTreatmentTime;
	int endTreatmentTime;

};
#endif