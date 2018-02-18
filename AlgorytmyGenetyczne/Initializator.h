#pragma once

#include "ProblemData.h"
#include "Population.h"

template <class T>
class Initializator {
protected:
	ProblemData<T>& _data;
public:
	Initializator(ProblemData<T>& data) : _data(data) {};
	virtual ~Initializator() {}

	virtual void initialize(Population<T>& pop) = 0;
};