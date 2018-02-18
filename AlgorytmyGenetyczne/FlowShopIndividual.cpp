#include "FlowShopIndividual.h"
#include <iostream>

#if defined(_DEBUG)
#include <cassert>
#endif


Individual<FlowShopProblem>::Individual(int jobsCount) {
	_jobsCount = jobsCount;
	_jobsSequence = new int[jobsCount];
}


Individual<FlowShopProblem>::~Individual() {
	delete [] _jobsSequence;
}

int& Individual<FlowShopProblem>::operator[](int job) {
	#if defined(_DEBUG)
	assert(job < _jobsCount && job >= 0);
	#endif
	return _jobsSequence[job];
}

int Individual<FlowShopProblem>::operator[](int ind) const {
	#if defined(_DEBUG)
	assert(ind < _jobsCount && ind >= 0);
	#endif
	return _jobsSequence[ind];
}

int Individual<FlowShopProblem>::getJobsCount() const {
	return _jobsCount;
}

std::ostream& operator<<(std::ostream& stream, Individual<FlowShopProblem>& ind) {
	for (int i = 0; i < ind.getJobsCount();++i) {
		stream << ind[i] << " ";
	}
	return stream;
}