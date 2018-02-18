#pragma once

#include "Population.h"

template <class T>
class MutationOperator {
protected:
	float _probability;
public:
	MutationOperator() {
		_probability = 0.0f;
	};
	virtual ~MutationOperator() {};

	void setProbability(float probability) {
		_probability = probability;
	}

	float getProbability() const{
		return _probability;
	}

	virtual void mutate(Population<T>& pop) {
		
	}

};

