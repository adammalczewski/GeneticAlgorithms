#include "FlowShopCrossOverOper.h"
#include <cstdlib>

FlowShopCrossOverOper::FlowShopCrossOverOper(int jobsCount) {
	_jobsCount = jobsCount;
	_isUsed1 = new bool[jobsCount];
	_isUsed2 = new bool[jobsCount];
	_temp = new int[jobsCount];
}


FlowShopCrossOverOper::~FlowShopCrossOverOper() {
	delete [] _isUsed1;
	delete [] _isUsed2;
	delete [] _temp;
}

void FlowShopCrossOverOper::crossOver(Population<FlowShopProblem>& pop) {

	int jobsCount = pop.getIndividuals()[0]->getJobsCount();
	if (jobsCount > _jobsCount) {
		delete [] _isUsed1;
		delete [] _isUsed2;
		delete [] _temp;
		_jobsCount = jobsCount;
		_isUsed1 = new bool[jobsCount];
		_isUsed2 = new bool[jobsCount];
		_temp = new int[jobsCount];
	}

	for (int i = 0; i < pop.getSize()/2; ++i){

		//get random individuals
		int firstInd = rand() % (pop.getSize()-i*2);
		int secondInd = rand() % (pop.getSize()-i*2);
		while (secondInd == firstInd) secondInd = rand() % (pop.getSize()-i*2);

		if ((float) rand() / RAND_MAX < _probability) {
			Individual<FlowShopProblem>* ind1 = pop.getIndividuals()[firstInd];
			Individual<FlowShopProblem>* ind2 = pop.getIndividuals()[secondInd];

			int cutPoint = rand() % ind1->getJobsCount();

			for (int j = 0; j < ind1->getJobsCount(); ++j) {
				_isUsed1[j] = false;
				_isUsed2[j] = false;
			}

			//which jobs are already set in the first individual
			for (int j = 0; j < cutPoint; ++j) {
				_isUsed1[(*ind1)[j]] = true;
			}

			//which jobs are set in the second individual
			for (int j = cutPoint; j < ind1->getJobsCount(); ++j) {
				_isUsed2[(*ind2)[j]] = true;
			}

			//copying new values for the second individual to temporary table
			int pos = 0;
			for (int j = 0; j < ind1->getJobsCount(); ++j) {
				if (!_isUsed2[(*ind1)[j]]) {
					_temp[pos++] = (*ind1)[j];
				}
			}

			//copying new values to the first individual
			pos = cutPoint;
			for (int j = 0; j < ind1->getJobsCount(); ++j) {
				if (!_isUsed1[(*ind2)[j]]) {
					(*ind1)[pos++] = (*ind2)[j];
				}
			}

			//copying values from temporary table to second individual
			for (int j = 0; j < cutPoint;++j) {
				(*ind2)[j] = _temp[j];
			}

		}

		//put them at the end of the table
		Individual<FlowShopProblem>* tempInd = pop.getIndividuals()[firstInd];
		pop.getIndividuals()[firstInd] = pop.getIndividuals()[pop.getSize() - 1 - i * 2];
		pop.getIndividuals()[pop.getSize() - 1 - i * 2] = tempInd;
		tempInd = pop.getIndividuals()[secondInd];
		pop.getIndividuals()[secondInd] = pop.getIndividuals()[pop.getSize() - 1 - i * 2 - 1];
		pop.getIndividuals()[pop.getSize() - 1 - i * 2 - 1] = tempInd;

	}

}