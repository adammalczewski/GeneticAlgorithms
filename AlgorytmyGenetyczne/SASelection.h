#pragma once

#include "SelectionOperator.h"
#include "Population.h"
#include <cmath>

template <class T>
class SASelection : public SelectionOperator<T> {
private:
	float T0 = 500.0;
	float t = 0;
	float tv = 1.2f;

	float getT() const{
		return T0*std::pow(tv,-t);
	}

public:

	void setT0(float _T0) {
		T0 = _T0;
	}

	void reset() {
		t = 0;
	}

	const float& getTv() const {
		return tv;
	}

	void setTv(const float tv) {
		this->tv = tv;
	}

	SASelection<T>(){
		
	}

	virtual void select(Population<T>&pop, float* values) override {

		if (pop.getSize() <= 1) return;

		//ommiting first individual, because he's the best current
		float bestValue = values[1];
		int bestInd = 1;
		for (int i = 2; i < pop.getSize(); ++i) {
			if (values[i] < bestValue) {
				bestInd = i;
				bestValue = values[i];
			}
		}

 		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		Individual<T>* bestIndPtr = pop.getIndividuals()[bestInd];


		//deleting not used individuals
		for (int i = 1; i < pop.getSize(); ++i) if (bestInd != i) {
			delete pop.getIndividuals()[i];
		}

		if (bestValue <= values[0]) {
			//changing current best
			delete pop.getIndividuals()[0];
		} else {
			float r = static_cast<float>(rand()) / RAND_MAX;
			++t;
			if (r < exp((values[0] - bestValue) / getT())) {
				//changing, even if the next is worse
				delete pop.getIndividuals()[0];
			} else {
				
				delete bestIndPtr;
				bestIndPtr = pop.getIndividuals()[0];
			}
		}

		delete[] pop.getIndividuals();

		pop.setIndividuals(new Individual<T>*[1]);
		pop.getIndividuals()[0] = bestIndPtr;

	}

};
