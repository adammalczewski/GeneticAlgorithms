#pragma once
#include "TabuNeighbourhoodSelector.h"
#include "FlowShopProblem.h"
#include "FlowShopIndividual.h"
#include <vector>

class FlowShopTabuNeighbourhoodOperSwapAll : public TabuNeighbourhoodSelector<FlowShopProblem> {
public:

	FlowShopTabuNeighbourhoodOperSwapAll() : TabuNeighbourhoodSelector<FlowShopProblem>() {
	}

	virtual void mutate(Population<FlowShopProblem>& pop) override {

		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		std::vector<int> tabuBlockedFirstJobs;
		std::vector<int> tabuBlockedSecondJobs;

		for (std::list<Individual<FlowShopProblem>*>::iterator it = _tabuTable.begin(); it != _tabuTable.end();++it) {
			Individual<FlowShopProblem>& ind = **it;
			int firstDiff;
			int secondDiff;
			int diffsCount = 0;
			for (int j = 0;diffsCount <= 2 && j < jobsCount;++j) {
				if (pop.getIndividuals()[0]->operator[](j) != ind[j]) {
					++diffsCount;
					if (diffsCount == 2) secondDiff = j;
					else firstDiff = j;
				}
			}
			if (diffsCount == 2) {
				tabuBlockedFirstJobs.push_back(firstDiff);
				tabuBlockedSecondJobs.push_back(secondDiff);
			}
		}

		int totalNeighSize = (jobsCount*(jobsCount - 1)) / 2 - tabuBlockedFirstJobs.size();
		int size = min(totalNeighSize, _neighbourhoodSize);

		Individual<FlowShopProblem>** newIndividuals = new Individual<FlowShopProblem>*[size];
		int pos = 0;

		if (_neighbourhoodSize < totalNeighSize*7/10) {
			while (pos < size){
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
		} else {

			Individual<FlowShopProblem>** totalNeighbourhood;

			if (size == totalNeighSize) totalNeighbourhood = newIndividuals;
			else {
				totalNeighbourhood = new Individual<FlowShopProblem>*[totalNeighSize];
			}

			for (int firstJob = 0; firstJob < jobsCount; ++firstJob)
				for (int secondJob = firstJob + 1; secondJob < jobsCount; ++secondJob) {

					//search the tabu table
					bool foundInTabu = false;
					for (int i = 0; !foundInTabu && i < tabuBlockedFirstJobs.size(); ++i) {
						if (tabuBlockedFirstJobs[i] == firstJob && tabuBlockedSecondJobs[i] == secondJob)
							foundInTabu = true;
					}

					if (!foundInTabu) {
						totalNeighbourhood[pos] = new Individual<FlowShopProblem>(jobsCount);
						for (int j = 0; j < jobsCount; ++j) {
							totalNeighbourhood[pos]->operator[](j) = pop.getIndividuals()[0]->operator[](j);
						}
						int temp = (*totalNeighbourhood[pos])[firstJob];
						(*totalNeighbourhood[pos])[firstJob] = (*totalNeighbourhood[pos])[secondJob];
						(*totalNeighbourhood[pos])[secondJob] = temp;
						++pos;
					}

				}

			if (size != totalNeighSize) {
				int actualSize = totalNeighSize;
				while (actualSize > size) {
					
					int toRemove = rand() % actualSize;

					Individual<FlowShopProblem>* temp = totalNeighbourhood[actualSize - 1];
					totalNeighbourhood[actualSize - 1] = totalNeighbourhood[toRemove];
					totalNeighbourhood[toRemove] = temp;

					--actualSize;
				}

				for (int i = 0; i < size;++i) {
					newIndividuals[i] = totalNeighbourhood[i];
				}

				for (int i = size; i < totalNeighSize; ++i) delete totalNeighbourhood[i];

				delete [] totalNeighbourhood;

			}

		}



		delete pop.getIndividuals()[0];
		delete [] pop.getIndividuals();

		pop.setIndividuals(newIndividuals);
		pop.setSize(size);

	}

};
