#pragma once
#include "TabuNeighbourhoodSelector.h"
#include "FlowShopProblem.h"
#include "FlowShopIndividual.h"
#include <vector>
#include <algorithm>

class FlowShopTabuNeighbourhoodOperSwapFewTimes : public TabuNeighbourhoodSelector<FlowShopProblem> {
private:
	int _swapTimes;
public:

	FlowShopTabuNeighbourhoodOperSwapFewTimes() : TabuNeighbourhoodSelector<FlowShopProblem>() {
		_swapTimes = 5;
	}

	const int& getSwapTimes() const {
		return _swapTimes;
	}

	void setSwapTimes(const int swapTimes) {
		_swapTimes = swapTimes;
	}

	virtual void mutate(Population<FlowShopProblem>& pop) override {

		/*
		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		std::vector<Individual<FlowShopProblem>&> tabuPossibleChoices;

		for (std::list<Individual<FlowShopProblem>*>::iterator it = _tabuTable.begin(); it != _tabuTable.end(); ++it) {
			Individual<FlowShopProblem>& ind = **it;
			int diffsCount = 0;
			for (int j = 0; diffsCount <= _swapTimes*2 && j < jobsCount; ++j) {
				if (pop.getIndividuals()[0]->operator[](j) != ind[j]) {
					++diffsCount;
				}
			}
			if (diffsCount <= _swapTimes*2) {
				tabuPossibleChoices.push_back(ind);
			}
		}

		Individual<FlowShopProblem>** newIndividuals = new Individual<FlowShopProblem>*[_neighbourhoodSize];
		int pos = 0;

		while (pos < _neighbourhoodSize) {
			int firstJob;
			int secondJob;

			do {
				firstJob = rand() % (jobsCount - 1);
				secondJob = rand() % (jobsCount - 1);
			} while (firstJob == secondJob);

			if (firstJob > secondJob) {
				int temp = firstJob;
				firstJob = secondJob;
				secondJob = temp;
			}

			//search the tabu table
			bool foundInTabu = false;
			for (int i = 0; !foundInTabu && i < tabuBlockedFirstJobs.size(); ++i) {
				if (tabuBlockedFirstJobs[i] == firstJob && tabuBlockedSecondJobs[i] == secondJob)
					foundInTabu = true;
			}

			if (!foundInTabu) {
				newIndividuals[pos] = new Individual<FlowShopProblem>(jobsCount);
				for (int j = 0; j < jobsCount; ++j) {
					newIndividuals[pos]->operator[](j) = pop.getIndividuals()[0]->operator[](j);
				}
				int temp = (*newIndividuals[pos])[firstJob];
				(*newIndividuals[pos])[firstJob] = (*newIndividuals[pos])[secondJob];
				(*newIndividuals[pos])[secondJob] = temp;
				++pos;
			}

		}

		delete pop.getIndividuals()[0];
		delete [] pop.getIndividuals();

		pop.setIndividuals(newIndividuals);
		pop.setSize(size);*/

	}

};
