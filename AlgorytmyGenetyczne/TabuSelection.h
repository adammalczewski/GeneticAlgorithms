#pragma once
#include "SelectionOperator.h"
#include "Population.h"

template <class T>
class TabuSelection : public SelectionOperator<T> {

	virtual void select(Population<T>&pop, float* values) override {
		
	}

};
