#pragma once
#include "TabuNeighbourhoodSelector.h"
#include "FlowShopProblem.h"
#include "FlowShopIndividual.h"
#include <vector>

class FlowShopTabuNeighbourhoodOperSwapClose : public TabuNeighbourhoodSelector<FlowShopProblem> {
public:

	FlowShopTabuNeighbourhoodOperSwapClose() : TabuNeighbourhoodSelector<FlowShopProblem>() {

	}

	virtual void mutate(Population<FlowShopProblem>& pop) override {

		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		std::vector<int> tabuBlockedFirstJobs;

		for (std::list<Individual<FlowShopProblem>*>::iterator it = _tabuTable.begin(); it != _tabuTable.end(); ++it) {
			Individual<FlowShopProblem>& ind = **it;
			int firstDiff;
			int secondDiff;
			int diffsCount = 0;
			for (int j = 0; diffsCount <= 2 && j < jobsCount; ++j) {
				if (pop.getIndividuals()[0]->operator[](j) != ind[j]) {
					++diffsCount;
					if (diffsCount == 2) {
						secondDiff = j;
						if (secondDiff != firstDiff + 1) {
							++diffsCount; //instead of break
						}
					} else firstDiff = j;
				}
			}
			if (diffsCount == 2) {
				tabuBlockedFirstJobs.push_back(firstDiff);
			}
		}

		Individual<FlowShopProblem>** newIndividuals = new Individual<FlowShopProblem>*[jobsCount-1-tabuBlockedFirstJobs.size()];
		int pos = 0;

		for (int firstJob = 0; firstJob < jobsCount-1; ++firstJob){

			int secondJob = firstJob + 1;

				//search the tabu table
				bool foundInTabu = false;
				for (int i = 0; !foundInTabu && i < tabuBlockedFirstJobs.size(); ++i) {
					if (tabuBlockedFirstJobs[i] == firstJob)
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
		pop.setSize(jobsCount-1 - tabuBlockedFirstJobs.size());

	}

};
