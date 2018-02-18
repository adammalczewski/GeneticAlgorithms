#pragma once

#include "SelectionOperator.h"

template <class T>
class TournamentSelection : public SelectionOperator<T>{
private:
	int _tournamentSize;
public:
	explicit TournamentSelection(int tournamentSize){
		_tournamentSize = tournamentSize;
	};
	~TournamentSelection() {};

	void setTournamentSize(int size) {
		_tournamentSize = size;
	}

	int getTournamentSize() const {
		return _tournamentSize;
	}

	void select(Population<T>&pop, float* values) override {

		int* staysTimes = new int[pop.getSize()];

		for (int i = 0; i < pop.getSize(); ++i) {
			staysTimes[i] = 0;
		}
		
		for (int i = 0; i < pop.getSize(); ++i){
			
			int bestInd = rand() % pop.getSize();
			float bestValue = values[bestInd];
			
			for (int j = 1; j < _tournamentSize; ++j) {
				int indNum = rand() % pop.getSize();
				float value = values[indNum];
				if (value < bestValue){
					bestValue = value;
					bestInd = indNum;
				}
			}

			staysTimes[bestInd]++;
		}

		int firstDeleted = 0;
		int jobsCount = pop.getIndividuals()[0]->getJobsCount();

		for (int i = 0; i < pop.getSize(); ++i) while (staysTimes[i] > 1) {
			
			//searching for the first deleted
			while (staysTimes[firstDeleted] != 0) ++firstDeleted;

			values[firstDeleted] = values[i];
			for (int j = 0; j < jobsCount; ++j) pop.getIndividuals()[firstDeleted]->operator[](j)
				= pop.getIndividuals()[i]->operator[](j);

			++firstDeleted;
			--staysTimes[i];
		}

		delete [] staysTimes;

	}

};
