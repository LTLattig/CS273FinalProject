#pragma once
#ifndef PATIENT_
#define PATIENT_
#include <string>
struct Patient
{

	Patient(int clock, int severity,std::string name) : arrivalTime(clock), treatmentTime(-1), startTreatmentTime(-1), endTreatmentTime(-1),name(name), severity(severity){}
	Patient(std::string name) : name(name) {}
	std::string name;
	int severity;
	int treatmentTime;
	int arrivalTime;
	int startTreatmentTime;
	int endTreatmentTime;
	bool operator<(const Patient &other) const
	{
		if (name < other.name)
			return true;
		else
			return false;
	}

};
#endif