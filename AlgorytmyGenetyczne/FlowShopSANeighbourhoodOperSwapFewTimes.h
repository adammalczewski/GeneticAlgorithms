#pragma once
#include "FlowShopProblem.h"
#include "FlowShopIndividual.h"
#include "SANeighbourhoodSelector.h"
#include <algorithm>

class FlowShopSANeighbourhoodOperSwapFewTimes : public SANeighbourhoodSelector<FlowShopProblem> {
private:
	int _swapTimes;
public:

	FlowShopSANeighbourhoodOperSwapFewTimes() : SANeighbourhoodSelector<FlowShopProblem>() {
		_swapTimes = 5;
	}

	const int& getSwapTimes() const {
		return _swapTimes;
	}

	void setSwapTimes(const int swapTimes) {
		_swapTimes = swapTimes;
	}

	virtual void mutate(Population<FlowShopProblem>& pop) override {

		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		Individual<FlowShopProblem>** newIndividuals = new Individual<FlowShopProblem>*[_neighbourhoodSize + 1];

		for (int i = 0; i < _neighbourhoodSize;++i) {
			newIndividuals[i + 1] = new Individual<FlowShopProblem>(jobsCount);
			for (int j = 0; j < jobsCount;++j) {
				newIndividuals[i + 1]->operator[](j) = pop.getIndividuals()[0]->operator[](j);
			}
			for (int s = 0; s < _swapTimes;++s) {
				int firstJob = rand() % jobsCount;
				int secondJob = rand() % jobsCount;
				int temp = (*newIndividuals[i+1])[firstJob];
				(*newIndividuals[i + 1])[firstJob] = (*newIndividuals[i + 1])[secondJob];
				(*newIndividuals[i + 1])[secondJob] = temp;
			}
		}

		newIndividuals[0] = pop.getIndividuals()[0];
		delete[] pop.getIndividuals();

		pop.setIndividuals(newIndividuals);
		pop.setSize(_neighbourhoodSize + 1);

	}

};