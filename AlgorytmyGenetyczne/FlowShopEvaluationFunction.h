#pragma once

#include "EvaluationFunction.h"
#include "FlowShopProblem.h"
#include "FlowShopProblemData.h"
#include "FlowShopIndividual.h"

class FlowShopEvaluationFunction : public EvaluationFunction<FlowShopProblem>{
private:
	int* _endTimes;

	FlowShopEvaluationFunction(FlowShopEvaluationFunction& evalFunction);
public:
	FlowShopEvaluationFunction(ProblemData<FlowShopProblem>& data);
	~FlowShopEvaluationFunction();

	float evaluate(Individual<FlowShopProblem>& ind);

};

