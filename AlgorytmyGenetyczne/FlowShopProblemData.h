#pragma once

#include "ProblemData.h"
#include "FlowShopProblem.h"

template <>
class ProblemData<FlowShopProblem>{
	int _jobsCount;
	int _machinesCount;
	int** _executionTimes;
	ProblemData(ProblemData<FlowShopProblem>& problemData);
public:
	ProblemData();
	~ProblemData();

	void loadFromFile(std::string fileName);

	int** executionTimes() {
		return _executionTimes;
	}

	int getMachinesCount() {
		return _machinesCount;
	}

	int getJobsCount() {
		return _jobsCount;
	}

	int operator[](int i) { return i; }

};

