#pragma once

#include "Statistics.h"
#include "Individual.h"
#include "EvaluationFunction.h"

template <class T>
class Population {
private:
	Individual<T> **_individuals;
	int _size;
	Population(Population<T>& pop);
public:

	Population(int size){
		_individuals = new Individual<T>*[size];
		for (int i = 0; i < size; ++i) _individuals[i] = nullptr;
		_size = size;
	}

	~Population() {
		for (int i = 0; i < _size; ++i) if (_individuals[i] != nullptr) delete _individuals[i];
		delete [] _individuals;
	}

	Individual<T>** getIndividuals() {
		return _individuals;
	}

	void setIndividuals(Individual<T>** individuals){
		_individuals = individuals;
	}

	int getSize() const {
		return _size;
	}

	void setSize(int size) {
		_size = size;
	}

	Statistics getStatistics(EvaluationFunction<T>& evaluationFunction) const {
		float firstValue = evaluationFunction.evaluate(*_individuals[0]);
		Statistics stats(firstValue, firstValue, firstValue,0.0f,0.0f);
		for (int i = 1; i < _size; ++i) {
			float value = evaluationFunction.evaluate(*_individuals[i]);
			if (value < stats.bestValue) {
				stats.bestValue = value;
			} else if (value > stats.worstValue) {
				stats.worstValue = value;
			}
			stats.avgValue += value;
		}
		stats.avgValue /= _size;

		for (int i = 0; i < _size;++i) {
			float value = evaluationFunction.evaluate(*_individuals[i]);
			stats.deviation += (value - stats.avgValue)*(value - stats.avgValue);
			if (value == stats.bestValue) {
				stats.bestValuePercentage += 1.0f;
			}
		}

		stats.deviation = sqrtf(stats.deviation / _size);
		stats.bestValuePercentage *= 100.0f/_size;

		return stats;
	}

	float* getValues(EvaluationFunction<T>& evaluationFunction) const {
		float* result = new float[_size];
		for (int i = 0; i < _size;++i) {
			result[i] = evaluationFunction.evaluate(*_individuals[i]);
		}
		return result;
	}

	Statistics getStatistics(float* values) const {
		Statistics stats(values[0], values[0], values[0],0.0f,0.0f);
		for (int i = 1; i < _size; ++i) {
			if (values[i] < stats.bestValue) {
				stats.bestValue = values[i];
			} else if (values[i] > stats.worstValue) {
				stats.worstValue = values[i];
			}
			stats.avgValue += values[i];
		}
		stats.avgValue /= _size;

		for (int i = 0; i < _size; ++i) {
			stats.deviation += (values[i] - stats.avgValue)*(values[i] - stats.avgValue);
			if (values[i] == stats.bestValue) {
				stats.bestValuePercentage += 1.0f;
			}
		}

		stats.deviation = sqrtf(stats.deviation / _size);
		stats.bestValuePercentage *= 100.0f / _size;

		return stats;
	}

};

