#pragma once
#include "FlowShopProblem.h"
#include "FlowShopIndividual.h"
#include "SANeighbourhoodSelector.h"
#include <algorithm>

class FlowShopSANeighbourhoodOperReposition : public SANeighbourhoodSelector<FlowShopProblem> {
public:

	FlowShopSANeighbourhoodOperReposition() : SANeighbourhoodSelector<FlowShopProblem>() {
	}

	virtual void mutate(Population<FlowShopProblem>& pop) override {

		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		Individual<FlowShopProblem>** newIndividuals = new Individual<FlowShopProblem>*[_neighbourhoodSize + 1];

		for (int i = 0; i < _neighbourhoodSize; ++i) {
			newIndividuals[i + 1] = new Individual<FlowShopProblem>(jobsCount);
			for (int j = 0; j < jobsCount; ++j) {
				newIndividuals[i + 1]->operator[](j) = pop.getIndividuals()[0]->operator[](j);
			}
			int job = rand() % jobsCount;
			int place = rand() % jobsCount;
			int jobCopy = (*newIndividuals[i + 1])[job];
			if (job < place) {
				for (int j = job; j < place;++j) {
					(*newIndividuals[i + 1])[j] = (*newIndividuals[i + 1])[j + 1];
				}
			} else {
				for (int j = job; j > place; --j) {
					(*newIndividuals[i + 1])[j] = (*newIndividuals[i + 1])[j - 1];
				}
			}
			(*newIndividuals[i + 1])[place] = jobCopy;
		}

		newIndividuals[0] = pop.getIndividuals()[0];
		delete [] pop.getIndividuals();

		pop.setIndividuals(newIndividuals);
		pop.setSize(_neighbourhoodSize + 1);

	}

};