#pragma once

#include "FlowShopIndividual.h"


template <class T>
class CrossOverOperator {
protected:
	float _probability;
public:
	CrossOverOperator()
	{
		_probability = 0;
	};
	virtual ~CrossOverOperator() {};

	void setProbability(float probability) {
		_probability = probability;
	}

	float getProbability() const {
		return _probability;
	}

	virtual void crossOver(Population<T>& pop) {
		
	}

};

