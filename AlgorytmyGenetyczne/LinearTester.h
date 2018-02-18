#pragma once
#include <vector>
#include <functional>
#include <string>
#include <sstream>
#include "FlowShopProblem.h"
#include "EvolutionAlgorithm.h"
#include "Data.h"
#include "Table.h"
#include "timer.h"
#include "FlowShopRandomInitializator.h"
#include "FlowShopMutationOper.h"
#include "FlowShopCrossOverOper.h"
#include "TournamentSelection.h"
#include "FlowShopEvaluationFunction.h"
#include "FlowShopTabuNeighbourhoodOperSwapAll.h"
#include "TabuSearchAlgorithm.h"
#include "FlowShopSANeighbourhoodOperSwapAll.h"
#include "SAAlgorithm.h"
#include "Workbook.h"
#include "FlowShopSANeighbourhoodOperSwapFewTimes.h"
#include "FlowShopSANeighbourhoodOperReposition.h"
#include "FlowShopSANeighbourhoodOperReverseSequence.h"
#include "FlowShopSAInitializator.h"

enum NeighbourhoodType{
	Reposition,ReverseSequence,SwapAll,Swap2Times,Swap4Times,Swap8Times,Swap16Times
};

class LinearTester {
private:
	//evolution algorithm
	std::vector<int> _mvalues;
	std::vector<int> _cvalues;
	std::vector<int> _tvalues;
	std::vector<int> _gvalues;
	std::vector<int> _pvalues;

	//tabu search
	std::vector<int> _tivalues;
	std::vector<int> _ttvalues;
	std::vector<int> _tnvalues;

	//SA
	std::vector<int> _sivalues; //iterations' count
	std::vector<int> _s0values; //temperature at 0 time
	std::vector<int> _svvalues; //velocity of change
	std::vector<int> _snvalues; //neighbourhood size

	NeighbourhoodType _neighType;

	int _executionRepeatTimes;

public:

	LinearTester() {
		_executionRepeatTimes = 10;
		_neighType = NeighbourhoodType::Swap4Times;
	}

	const int& getExecutionRepeatTimes() const {
		return _executionRepeatTimes;
	}

	void setExecutionRepeatTimes(const int executionRepeatTimes) {
		_executionRepeatTimes = executionRepeatTimes;
	}

	const std::vector<int>& getMvalues() const {
		return _mvalues;
	}

	void setMvalues(const std::vector<int>& values) {
		_mvalues = values;
	}

	const std::vector<int>& getCvalues() const {
		return _cvalues;
	}

	void setCvalues(const std::vector<int>& values) {
		_cvalues = values;
	}

	const std::vector<int>& getTvalues() const {
		return _tvalues;
	}

	void setTvalues(const std::vector<int>& values) {
		_tvalues = values;
	}

	const std::vector<int>& getGvalues() const {
		return _gvalues;
	}

	void setGvalues(const std::vector<int>& values) {
		_gvalues = values;
	}

	const std::vector<int>& getPvalues() const {
		return _pvalues;
	}

	void setPvalues(const std::vector<int>& values) {
		_pvalues = values;
	}

	const std::vector<int>& getTivalues() const {
		return _tivalues;
	}

	void setTivalues(const std::vector<int>& is) {
		_tivalues = is;
	}

	const std::vector<int>& getTtvalues() const {
		return _ttvalues;
	}

	void setTtvalues(const std::vector<int>& is) {
		_ttvalues = is;
	}

	const std::vector<int>& getTnvalues() const {
		return _tnvalues;
	}

	void setTnvalues(const std::vector<int>& is) {
		_tnvalues = is;
	}

	const std::vector<int>& getS0values() const {
		return _s0values;
	}

	void setS0values(const std::vector<int>& is) {
		_s0values = is;
	}

	const std::vector<int>& getSvvalues() const {
		return _svvalues;
	}

	void setSvvalues(const std::vector<int>& is) {
		_svvalues = is;
	}

	const std::vector<int>& getSnvalues() const {
		return _snvalues;
	}

	void setSnvalues(const std::vector<int>& is) {
		_snvalues = is;
	}

	const std::vector<int>& getSivalues() const {
		return _sivalues;
	}

	void setSivalues(const std::vector<int>& is) {
		_sivalues = is;
	}

	const NeighbourhoodType& getNeighType() const {
		return _neighType;
	}

	void setNeighType(const NeighbourhoodType neighbourhoodType) {
		_neighType = neighbourhoodType;
	}

private:

	template <class T>
	T adjustSingleParameter(EvolutionAlgorithm<FlowShopProblem>& algorithm, std::vector<T>& values, const std::string& parameterName
		, excel::Workbook& excelWorkbook, std::function<void(T)> changeFunc, int iterationNum, int paramNum) {

		float bestValue = 100000;
		T best = 0;

		for (int i = 0; i < values.size(); ++i) {

			changeFunc(values[i]);

			std::stringstream sstream;
			sstream << parameterName << " : " << (values[i]);

			std::vector<std::vector<Statistics>> result = algorithm.executeMultipleTimes(_executionRepeatTimes,nullptr);

			excelWorkbook.addGraph(NamedStatisticsSeries(result[0], sstream.str()));
			Statistics bestResult = Statistics::bestStatistics(result[1]);
			excel::Data data(bestResult);
			data.addParameter(excel::NamedValue(parameterName, values[i]));
			excelWorkbook.addData(data);
			if (bestResult.bestValue < bestValue) {
				bestValue = bestResult.bestValue;
				best = values[i];
			}

			std::cout << "skonczone : " << sstream.str() << std::endl;

		}

		std::cout << "wybrano - " << parameterName << " : " << best << std::endl;
		changeFunc(best);

		excel::Data data;
		data.addValue(excel::NamedValue(parameterName, best));
		data.addParameter(excel::NamedValue("numer iteracji", iterationNum));
		excelWorkbook.addData(data);

		std::stringstream tableNameSStream;
		tableNameSStream << "Iteracja nr " << iterationNum << ": " << paramNum << ". " << parameterName;
		excelWorkbook.addTable(excel::Table({ parameterName }, Statistics::getTableValues(), tableNameSStream.str()));

		return best;
	}

	static std::vector<std::string> basicLoop(std::vector<std::string> fileNames, int begin, int end, int iteration, std::function<excel::Workbook(std::string)> researchFunc) {
		
		std::vector<std::string> resultsFileNames;

		for (int f = begin; f <= end && f < fileNames.size(); ++f) {

			Timer timer;
			timer.start();

			excel::Workbook excelWorkbook = researchFunc(fileNames[f]+".txt");

			float time = timer.getTime();

			//Saving the time
			excelWorkbook.addData(excel::Data({ excel::NamedValue("numer iteracji", 1) }, { excel::NamedValue("czas dzia³ania", static_cast<int>(time)) }));

			excelWorkbook.addTable(excel::Table({ "numer iteracji" }, { "czas dzia³ania" }, ""));

			excelWorkbook.saveToFile("exceldata" + fileNames[f] + ".txt", true);

			resultsFileNames.push_back("exceldata" + fileNames[f] + ".txt");

		}

		return resultsFileNames;

	}

	static SANeighbourhoodSelector<FlowShopProblem>* getSANeighbourhoodSelector(NeighbourhoodType neighType) {

		switch (neighType) {

		case Reposition: 
			return new FlowShopSANeighbourhoodOperReposition();
		case ReverseSequence: 
			return new FlowShopSANeighbourhoodOperReverseSequence();
		case SwapAll: 
			return new FlowShopSANeighbourhoodOperSwapAll();
		case Swap2Times: {
			FlowShopSANeighbourhoodOperSwapFewTimes* swap2TimesSelector = new FlowShopSANeighbourhoodOperSwapFewTimes();
			swap2TimesSelector->setSwapTimes(2);
			return swap2TimesSelector;
		}
		case Swap4Times: {
			FlowShopSANeighbourhoodOperSwapFewTimes* swap4TimesSelector = new FlowShopSANeighbourhoodOperSwapFewTimes();
			swap4TimesSelector->setSwapTimes(4);
			return swap4TimesSelector;
		}
		case Swap8Times: {
			FlowShopSANeighbourhoodOperSwapFewTimes* swap8TimesSelector = new FlowShopSANeighbourhoodOperSwapFewTimes();
			swap8TimesSelector->setSwapTimes(8);
			return swap8TimesSelector;
		}
		case Swap16Times: {
			FlowShopSANeighbourhoodOperSwapFewTimes* swap16TimesSelector = new FlowShopSANeighbourhoodOperSwapFewTimes();
			swap16TimesSelector->setSwapTimes(16);
			return swap16TimesSelector;
		}
		default: 
			return nullptr;
		}

	}

public:

	std::vector<std::string> testSA(std::vector<std::string> fileNames, int begin, int end, int iteration) {
		
		return basicLoop(fileNames,begin,end,iteration,[this,iteration](std::string fileName){

			excel::Workbook excelWorkbook;
			
			ProblemData<FlowShopProblem> problemData;
			problemData.loadFromFile(fileName);

			FlowShopRandomInitializator initializator(problemData);
			FlowShopEvaluationFunction evaluationFunc(problemData);
			SANeighbourhoodSelector<FlowShopProblem>* neighbourhoodSelector = getSANeighbourhoodSelector(_neighType);

			SAAlgorithm<FlowShopProblem> algorithm(*neighbourhoodSelector, evaluationFunc, initializator);

			algorithm.setT0(_s0values[_s0values.size() / 2]);
			algorithm.setTv(_svvalues[_svvalues.size() / 2] / 100.0f);
			neighbourhoodSelector->setNeighbourhoodSize(_snvalues[_snvalues.size() / 2]);
			algorithm.stopCondition().setGenerationsCount(_sivalues[_sivalues.size() / 2]);

			/* temperatura pocz¹tkowa <0 - ...) */
			float bestt0 = adjustSingleParameter<int>(algorithm, _s0values, "temperatura pocz¹tkowa", excelWorkbook, [&algorithm](int t0) {
				algorithm.setT0(t0);
			}, iteration, 1);

			/* prêdkoœæ spadku temperatury (100 - ...)*/
			float besttv = adjustSingleParameter<int>(algorithm, _svvalues, "prêdkoœæ spadku temperatury", excelWorkbook, [&algorithm](int tv) {
				algorithm.setTv(tv / 100.0f);
			}, iteration, 2);

			/* wielkoœæ s¹siedztwa */
			float bestn = adjustSingleParameter<int>(algorithm, _snvalues, "wielkoœæ s¹siedztwa", excelWorkbook, [&neighbourhoodSelector](int neighSize) {
				neighbourhoodSelector->setNeighbourhoodSize(neighSize);
			}, iteration, 3);

			/* liczba iteracji */
			float bestsi = adjustSingleParameter<int>(algorithm, _sivalues, "liczba iteracji", excelWorkbook, [&algorithm](int iterationsCount) {
				algorithm.stopCondition().setGenerationsCount(iterationsCount);
			}, iteration, 4);

			excelWorkbook.addTable(excel::Table({ "numer iteracji" }, { "temperatura pocz¹tkowa","prêdkoœæ spadku temperatury","wielkoœæ s¹siedztwa","liczba iteracji" }
			, "wyliczone wartoœci"));
			
			delete neighbourhoodSelector;

			return excelWorkbook;

		});

	}

	std::vector<std::string> testHybrid(std::vector<std::string> fileNames, int begin, int end, int iteration) {

		return basicLoop(fileNames, begin, end, iteration, [this, iteration](std::string fileName) {

			excel::Workbook excelWorkbook;

			ProblemData<FlowShopProblem> problemData;

			problemData.loadFromFile(fileName);

			FlowShopSAInitializator initializator(problemData);

			//TODO initializator parameters

			FlowShopMutationOper mutationOper;
			FlowShopCrossOverOper crossOverOper(problemData.getJobsCount());

			TournamentSelection<FlowShopProblem> selectionOper(5);
			FlowShopEvaluationFunction evaluationFunc(problemData);

			EvolutionAlgorithm<FlowShopProblem> evolutionAlgorithm(mutationOper, crossOverOper, selectionOper, evaluationFunc, initializator);

			evolutionAlgorithm.stopCondition().setGenerationsCount(_gvalues[_gvalues.size() / 2]);
			evolutionAlgorithm.setPopulationSize(_pvalues[_pvalues.size() / 2]);
			mutationOper.setProbability(_mvalues[_mvalues.size() / 2]);
			crossOverOper.setProbability(_cvalues[_cvalues.size() / 2]);
			selectionOper.setTournamentSize(_tvalues[_tvalues.size() / 2]);

			// mutacja
			float bestm = adjustSingleParameter<int>(evolutionAlgorithm, _mvalues, "p-stwo mutacji", excelWorkbook, [&mutationOper](int mutationProb) {
				mutationOper.setProbability(mutationProb / 100.0f);
			}, iteration, 1);

			// krzy¿owanie
			float bestc = adjustSingleParameter<int>(evolutionAlgorithm, _cvalues, "p-stwo krzy¿owania", excelWorkbook, [&crossOverOper](int crossOverProb) {
				crossOverOper.setProbability(crossOverProb / 100.0f);
			}, iteration, 2);

			// wielkoœæ turnieju
			int bestt = adjustSingleParameter<int>(evolutionAlgorithm, _tvalues, "wielkoœæ turnieju", excelWorkbook, [&selectionOper](int tournamentSize) {
				selectionOper.setTournamentSize(tournamentSize);
			}, iteration, 3);

			// liczba pokoleñ
			int bestg = adjustSingleParameter<int>(evolutionAlgorithm, _gvalues, "liczba pokoleñ", excelWorkbook, [&evolutionAlgorithm](int generationsCount) {
				evolutionAlgorithm.stopCondition().setGenerationsCount(generationsCount);
			}, iteration, 4);

			// wielkoœæ populacji
			int bestp = adjustSingleParameter<int>(evolutionAlgorithm, _pvalues, "wielkoœæ populacji", excelWorkbook, [&evolutionAlgorithm](int popSize) {
				evolutionAlgorithm.setPopulationSize(popSize);
			}, iteration, 5);

			excelWorkbook.addTable(excel::Table({ "numer iteracji" }, { "p-stwo mutacji","p-stwo krzy¿owania","wielkoœæ turnieju","liczba pokoleñ", "wielkoœc populacji" }
			, "wyliczone wartoœci"));

			return excelWorkbook;

		});

	}

	std::vector<std::string> testEvolutionAlgorithm(std::vector<std::string> fileNames, int begin, int end, int iteration) {

		return basicLoop(fileNames, begin, end, iteration, [this, iteration](std::string fileName) {

			excel::Workbook excelWorkbook;

			ProblemData<FlowShopProblem> problemData;

			problemData.loadFromFile(fileName);

			FlowShopRandomInitializator initializator(problemData);
			FlowShopMutationOper mutationOper;
			FlowShopCrossOverOper crossOverOper(problemData.getJobsCount());

			TournamentSelection<FlowShopProblem> selectionOper(5);
			FlowShopEvaluationFunction evaluationFunc(problemData);

			EvolutionAlgorithm<FlowShopProblem> evolutionAlgorithm(mutationOper, crossOverOper, selectionOper, evaluationFunc, initializator);

			evolutionAlgorithm.stopCondition().setGenerationsCount(_gvalues[_gvalues.size() / 2]);
			evolutionAlgorithm.setPopulationSize(_pvalues[_pvalues.size() / 2]);
			mutationOper.setProbability(_mvalues[_mvalues.size() / 2]);
			crossOverOper.setProbability(_cvalues[_cvalues.size() / 2]);
			selectionOper.setTournamentSize(_tvalues[_tvalues.size() / 2]);

			// mutacja
			float bestm = adjustSingleParameter<int>(evolutionAlgorithm, _mvalues, "p-stwo mutacji", excelWorkbook, [&mutationOper](int mutationProb) {
				mutationOper.setProbability(mutationProb / 100.0f);
			}, iteration, 1);

			// krzy¿owanie
			float bestc = adjustSingleParameter<int>(evolutionAlgorithm, _cvalues, "p-stwo krzy¿owania", excelWorkbook, [&crossOverOper](int crossOverProb) {
				crossOverOper.setProbability(crossOverProb / 100.0f);
			}, iteration, 2);

			// wielkoœæ turnieju
			int bestt = adjustSingleParameter<int>(evolutionAlgorithm, _tvalues, "wielkoœæ turnieju", excelWorkbook, [&selectionOper](int tournamentSize) {
				selectionOper.setTournamentSize(tournamentSize);
			}, iteration, 3);

			// liczba pokoleñ
			int bestg = adjustSingleParameter<int>(evolutionAlgorithm, _gvalues, "liczba pokoleñ", excelWorkbook, [&evolutionAlgorithm](int generationsCount) {
				evolutionAlgorithm.stopCondition().setGenerationsCount(generationsCount);
			}, iteration, 4);

			// wielkoœæ populacji
			int bestp = adjustSingleParameter<int>(evolutionAlgorithm, _pvalues, "wielkoœæ populacji", excelWorkbook, [&evolutionAlgorithm](int popSize) {
				evolutionAlgorithm.setPopulationSize(popSize);
			}, iteration, 5);

			excelWorkbook.addTable(excel::Table({ "numer iteracji" }, { "p-stwo mutacji","p-stwo krzy¿owania","wielkoœæ turnieju","liczba pokoleñ", "wielkoœc populacji" }
			, "wyliczone wartoœci"));

			return excelWorkbook;

		});

	}

	std::vector<std::string> testTabuSearch(std::vector<std::string> fileNames, int begin, int end, int iteration) {

		return basicLoop(fileNames, begin, end, iteration, [this, iteration](std::string fileName) {

			excel::Workbook excelWorkbook;

			ProblemData<FlowShopProblem> problemData;

			problemData.loadFromFile(fileName);

			FlowShopRandomInitializator initializator(problemData);
			FlowShopEvaluationFunction evaluationFunc(problemData);
			FlowShopTabuNeighbourhoodOperSwapAll neighbourhoodSelector;

			TabuSearchAlgorithm<FlowShopProblem> algorithm(neighbourhoodSelector, evaluationFunc, initializator);

			algorithm.stopCondition().setGenerationsCount(_tivalues[_tivalues.size() / 2]);
			algorithm.setTabuTableSize(_ttvalues[_ttvalues.size() / 2]);
			neighbourhoodSelector.setNeighbourhoodSize(_tnvalues[_tnvalues.size() / 2]);


			// wielkoœæ tabu
			float besttt = adjustSingleParameter<int>(algorithm, _ttvalues, "wielkoœæ tabu", excelWorkbook, [&algorithm](int tabuSize) {
				algorithm.setTabuTableSize(tabuSize / 100.0f*algorithm.stopCondition().getGenerationsCount());
			}, iteration, 1);

			// wielkoœæ s¹siedztwa
			float besttn = adjustSingleParameter<int>(algorithm, _tnvalues, "wielkoœæ s¹siedztwa", excelWorkbook, [&neighbourhoodSelector](int neighSize) {
				neighbourhoodSelector.setNeighbourhoodSize(neighSize);
			}, iteration, 2);

			// liczba iteracji
			float bestti = adjustSingleParameter<int>(algorithm, _tivalues, "liczba iteracji", excelWorkbook, [&algorithm](int iterationsCount) {
				algorithm.stopCondition().setGenerationsCount(iterationsCount);
			}, iteration, 3);

			excelWorkbook.addTable(excel::Table({ "numer iteracji" }, { "liczba iteracji","wielkoœæ tabu","wielkoœæ s¹siedztwa" }
			, "wyliczone wartoœci"));

			return excelWorkbook;

		});

	}

};
