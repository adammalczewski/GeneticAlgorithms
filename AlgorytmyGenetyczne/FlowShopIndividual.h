#pragma once

#include "Individual.h"
#include "FlowShopProblem.h"
#include <iostream>

template <>
class Individual<FlowShopProblem>{
private:
	int* _jobsSequence;
	int _jobsCount;
	Individual(Individual<FlowShopProblem>& ind);
public:
	Individual() : Individual(1) {}
	explicit Individual(int jobsCount);
	~Individual();

	int& operator[](int ind);
	int operator[](int ind) const;

	int getJobsCount() const;

};

std::ostream& operator<<(std::ostream& stream, Individual<FlowShopProblem>& ind);