#pragma once
#include "Population.h"
#include "MutationOperator.h"
#include <list>

template <class T>
class TabuSearchAlgorithm;

template <class T>
class TabuNeighbourhoodSelector : MutationOperator<T> {
protected:
	std::list<Individual<T>*> _tabuTable;
	int _neighbourhoodSize;

	friend TabuSearchAlgorithm<T>;

public:
	TabuNeighbourhoodSelector(): _neighbourhoodSize(10) {}
	virtual ~TabuNeighbourhoodSelector() {

	};

	const int& getNeighbourhoodSize() const {
		return _neighbourhoodSize;
	}

	void setNeighbourhoodSize(const int neighbourhoodSize) {
		_neighbourhoodSize = neighbourhoodSize;
	}

	virtual void mutate(Population<T>& pop) override = 0;

};
