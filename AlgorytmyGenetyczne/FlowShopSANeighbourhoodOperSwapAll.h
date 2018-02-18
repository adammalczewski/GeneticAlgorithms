#pragma once
#include "FlowShopProblem.h"
#include "FlowShopIndividual.h"
#include <vector>
#include <cassert>
#include "SANeighbourhoodSelector.h"
#include <algorithm>

class FlowShopSANeighbourhoodOperSwapAll : public SANeighbourhoodSelector<FlowShopProblem> {
public:

	FlowShopSANeighbourhoodOperSwapAll() : SANeighbourhoodSelector<FlowShopProblem>() {
	}

	virtual void mutate(Population<FlowShopProblem>& pop) override {

		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		int totalNeighSize = (jobsCount*(jobsCount - 1)) / 2;
		int size = min(totalNeighSize, _neighbourhoodSize);

		Individual<FlowShopProblem>** newIndividuals = new Individual<FlowShopProblem>*[size+1];
		int pos = 1;

		if (_neighbourhoodSize < totalNeighSize * 7 / 10) {
			while (pos < size+1) {
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

				newIndividuals[pos] = new Individual<FlowShopProblem>(jobsCount);
				for (int j = 0; j < jobsCount; ++j) {
					newIndividuals[pos]->operator[](j) = pop.getIndividuals()[0]->operator[](j);
				}
				int temp = (*newIndividuals[pos])[firstJob];
				(*newIndividuals[pos])[firstJob] = (*newIndividuals[pos])[secondJob];
				(*newIndividuals[pos])[secondJob] = temp;
				++pos;

			}
		} else {

			Individual<FlowShopProblem>** totalNeighbourhood;

			if (size == totalNeighSize) totalNeighbourhood = newIndividuals;
			else {
				totalNeighbourhood = new Individual<FlowShopProblem>*[totalNeighSize+1];
			}

			pos = 1;

			for (int firstJob = 0; firstJob < jobsCount; ++firstJob)
				for (int secondJob = firstJob + 1; secondJob < jobsCount; ++secondJob) {

					totalNeighbourhood[pos] = new Individual<FlowShopProblem>(jobsCount);
					for (int j = 0; j < jobsCount; ++j) {
						totalNeighbourhood[pos]->operator[](j) = pop.getIndividuals()[0]->operator[](j);
					}
					int temp = (*totalNeighbourhood[pos])[firstJob];
					(*totalNeighbourhood[pos])[firstJob] = (*totalNeighbourhood[pos])[secondJob];
					(*totalNeighbourhood[pos])[secondJob] = temp;
					++pos;

				}

			if (size != totalNeighSize) {
				int actualSize = totalNeighSize;
				while (actualSize > size) {

					int toRemove = rand() % actualSize+1;

					Individual<FlowShopProblem>* temp = totalNeighbourhood[actualSize];
					totalNeighbourhood[actualSize] = totalNeighbourhood[toRemove];
					totalNeighbourhood[toRemove] = temp;

					--actualSize;
				}

				for (int i = 1; i < size+1; ++i) {
					newIndividuals[i] = totalNeighbourhood[i];
				}

				for (int i = size+1; i < totalNeighSize+1; ++i) delete totalNeighbourhood[i];

				delete [] totalNeighbourhood;

			}

		}

		newIndividuals[0] = pop.getIndividuals()[0];
		delete [] pop.getIndividuals();

		pop.setIndividuals(newIndividuals);
		pop.setSize(size+1);

	}

};
