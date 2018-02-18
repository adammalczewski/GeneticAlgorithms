#include "FlowShopMutationOper.h"
#include <cstdlib>
#include <iostream>

FlowShopMutationOper::FlowShopMutationOper() {
}


FlowShopMutationOper::~FlowShopMutationOper() {
}

void FlowShopMutationOper::mutate(Population<FlowShopProblem>& pop) {

	for (int i = 0; i < pop.getSize(); ++i){


		if (static_cast<float>(rand()) / RAND_MAX < _probability){
			
			Individual<FlowShopProblem>* ind = pop.getIndividuals()[i];
			int firstJob = rand() % ind->getJobsCount();
			int secondJob = rand() % ind->getJobsCount();
			while (secondJob == firstJob) secondJob = rand() % ind->getJobsCount();
			int temp = (*ind)[firstJob];
			(*ind)[firstJob] = (*ind)[secondJob];
			(*ind)[secondJob] = temp;

		}

	}

}
