#pragma once

#include "SelectionOperator.h"
#include "Population.h"
#include <list>

template <class T>
class TabuSlowSelection : public SelectionOperator<T> {
private:
	std::list<Individual<T>*>& _tabuTable;
	int _tabuTableSize;
public:

	explicit TabuSlowSelection<T>(std::list<Individual<T>*>& tabuTable): _tabuTable(tabuTable) {
		_tabuTableSize = 0;
	}

	void setTabuTableSize(int tabuTableSize) {
		_tabuTableSize = tabuTableSize;
	}

	int getTabuTableSize() const {
		return _tabuTableSize;
	}

	void clearTabuTable() const{
		_tabuTable.clear();
	}

	virtual void select(Population<T>&pop, float* values) override {

		int bestValue = values[0];
		int bestInd = 0;
		for (int i = 0; i < pop.getSize();++i) {
			if (values[i] < bestValue) {
				bestInd = i;
			}
		}

		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		//replicating best individual
		Individual<T>* bestIndPtr = new Individual<T>(jobsCount);
		for (int i = 0; i < jobsCount;++i) {
			bestIndPtr->operator[](i) = pop.getIndividuals()[bestInd]->operator[](i);
		}

		//deleting not used individuals
		for (int i = 0; i < pop.getSize();++i) if (bestInd != i) {
			delete pop.getIndividuals()[i];
		}
		

		_tabuTable.push_back(pop.getIndividuals()[bestInd]);
		if (_tabuTable.size() > _tabuTableSize) _tabuTable.pop_front();

		delete [] pop.getIndividuals();

		pop.setIndividuals(new Individual<T>*[1]);
		pop.getIndividuals()[0] = bestIndPtr;

	}

};
