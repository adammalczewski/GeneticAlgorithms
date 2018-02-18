#pragma once
#include "Population.h"
#include "MutationOperator.h"
#include <list>

template <class T>
class TabuSearchAlgorithm;

template <class T>
class SANeighbourhoodSelector : public MutationOperator<T> {
protected:
	int _neighbourhoodSize;
public:
	SANeighbourhoodSelector() {
		_neighbourhoodSize = 10;
	}
	virtual ~SANeighbourhoodSelector() {

	};

	const int& getNeighbourhoodSize() const {
		return _neighbourhoodSize;
	}

	void setNeighbourhoodSize(const int neighbourhoodSize) {
		_neighbourhoodSize = neighbourhoodSize;
	}


	virtual void mutate(Population<T>& pop) override = 0;

};
