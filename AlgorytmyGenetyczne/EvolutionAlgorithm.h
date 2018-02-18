#pragma once

#include "Population.h"
#include "CrossOverOperator.h"
#include "MutationOperator.h"
#include "SelectionOperator.h"
#include "EvaluationFunction.h"
#include "Initializator.h"
#include <vector>
#include "StopCondition.h"

template <class T>
class EvolutionAlgorithm {
protected:
	CrossOverOperator<T>& _crossOverOper;
	MutationOperator<T>& _mutationOper;
	SelectionOperator<T>& _selectionOper;
	EvaluationFunction<T>& _evaluationFunc;
	Initializator<T>& _initializator;

	int _populationSize;

	StopCondition _stopCondition;

public:

	const int STANDARD_POPULATION_SIZE = 1000;

	EvolutionAlgorithm(MutationOperator<T>& mutationOper, CrossOverOperator<T>& crossOverOper
		, SelectionOperator<T>& selectionOper, EvaluationFunction<T>& evaluationFunc, Initializator<T>& initializator) : _crossOverOper(crossOverOper), _mutationOper(mutationOper)
		, _selectionOper(selectionOper), _evaluationFunc(evaluationFunc), _initializator(initializator) {
		
		_populationSize = STANDARD_POPULATION_SIZE;
		_stopCondition.setGenerationsCountEnabled(true);
		_stopCondition.setGenerationsCount(1000);

	};

	virtual ~EvolutionAlgorithm() {};

	StopCondition& stopCondition() {
		return _stopCondition;
	}

	int getPopulationSize() const{
		return _populationSize;
	}

	void setPopulationSize(int populationSize) {
		_populationSize = populationSize;
	}

	virtual std::vector<Statistics> execute(Individual<T>** bestIndividual) {

		Population<T> pop(_populationSize);
		_initializator.initialize(pop);

		int generation = 0;
		std::vector<Statistics> result;

		while (_stopCondition.shouldContinue(generation)){

			float* values = pop.getValues(_evaluationFunc);
			result.push_back(pop.getStatistics(values));

			_selectionOper.select(pop, values);
			delete [] values;

			_mutationOper.mutate(pop);
			_crossOverOper.crossOver(pop);
			

			++generation;

		}

		if (bestIndividual != nullptr && pop.getSize() > 0) {
			float* values = pop.getValues(_evaluationFunc);

			float bestValue = values[0];
			int bestInd = 0;

			for (int i = 1; i < pop.getSize(); ++i) if (values[i] < bestValue) {
				bestValue = values[i];
				bestInd = i;
			}

			int jobsCount = pop.getIndividuals()[0]->getJobsCount();

			*bestIndividual = pop.getIndividuals()[bestInd];
			pop.getIndividuals()[bestInd] = new Individual<T>();

			delete [] values;
		}

		return result;

	}


	//Runs loops times and returns first values and overall values
	std::vector<std::vector<Statistics>> executeMultipleTimes(int loops, Individual<T>** bestIndividual) {

		std::vector<std::vector<Statistics>> statistics;

		for (int i = 0; i < loops; ++i) {

			statistics.push_back(execute(bestIndividual));

		}

		std::vector<Statistics> avgStatistics = Statistics::averageStatistics(statistics);

		std::vector<std::vector<Statistics>> results;

		results.push_back(statistics[0]);
		results.push_back(avgStatistics);

		return results;

	}


};

