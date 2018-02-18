#include "FlowShopRandomInitializator.h"

FlowShopRandomInitializator::FlowShopRandomInitializator(ProblemData<FlowShopProblem>& data): Initializator(data) {

}

void FlowShopRandomInitializator::initialize(Population<FlowShopProblem>& pop) {
	
	for (int i = 0; i < pop.getSize(); ++i) {
		pop.getIndividuals()[i] = new Individual<FlowShopProblem>(_data.getJobsCount());
		for (int j = 0; j < _data.getJobsCount(); ++j) pop.getIndividuals()[i]->operator[](j) = j;
		for (int j = 0; j < _data.getJobsCount() * 10; ++j) {
			int firstJob = rand() % _data.getJobsCount();
			int secondJob = rand() % _data.getJobsCount();
			int temp = pop.getIndividuals()[i]->operator[](firstJob);
			pop.getIndividuals()[i]->operator[](firstJob) = pop.getIndividuals()[i]->operator[](secondJob);
			pop.getIndividuals()[i]->operator[](secondJob) = temp;
		}
	}

}
