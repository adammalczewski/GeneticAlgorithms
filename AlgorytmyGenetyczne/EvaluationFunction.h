#pragma once

#include "ProblemData.h"
#include "Individual.h"

template <class T>
class EvaluationFunction{
protected:
	ProblemData<T>& _data;
public:
	EvaluationFunction(ProblemData<T>& data) : _data(data) {};
	virtual ~EvaluationFunction() {};

	virtual float evaluate(Individual<T>& ind) = 0;

};

