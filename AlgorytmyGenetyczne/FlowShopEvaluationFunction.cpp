#include "FlowShopEvaluationFunction.h"
#include <algorithm>


FlowShopEvaluationFunction::FlowShopEvaluationFunction(ProblemData<FlowShopProblem>& data) : EvaluationFunction(data) {
	_endTimes = new int[data.getJobsCount()];
}


FlowShopEvaluationFunction::~FlowShopEvaluationFunction() {
	delete [] _endTimes;
}

float FlowShopEvaluationFunction::evaluate(Individual<FlowShopProblem>& ind) {
	_endTimes[0] = _data.executionTimes()[0][ind[0]];
	for (int i = 1; i < _data.getJobsCount(); ++i) _endTimes[i] = _endTimes[i-1] + _data.executionTimes()[0][ind[i]];
	for (int i = 1; i < _data.getMachinesCount(); ++i){
		_endTimes[0] = _endTimes[0] + _data.executionTimes()[i][ind[0]];
		for (int j = 1; j < _data.getJobsCount(); ++j){
			_endTimes[j] = std::max(_endTimes[j - 1], _endTimes[j]) + _data.executionTimes()[i][ind[j]];
		}
	}
	return (float)_endTimes[_data.getJobsCount() - 1];
}
