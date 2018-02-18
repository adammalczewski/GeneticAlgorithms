#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include "LinearTester.h"

using namespace std;

enum MetaheuristicType {
	EvolutionAlgorithms,TabuSearch,SA
};

enum CalculationTime {
	VeryFast,Fast,Slow
};

void setParametersForEvolutionAlgorithm(LinearTester& linearTester, CalculationTime calculationTime,int fileNumber, int iteration) {

	/* PIERWSZA ITERACJA */
	/*
	switch (fileNumber) {
	case 0:
	linearTester.setMvalues({ 20,30,40,50,60,70,80 });
	linearTester.setCvalues({ 20,30,40,50,60,70,80 });
	linearTester.setTvalues({ 1,2,4,6,8,12,20 });
	linearTester.setGvalues({ 50,100,200,500,1000,2000,5000 });
	linearTester.setPvalues({ 500, 1250, 2500, 5000, 12500, 25000, 50000 });
	break;
	case 1:
	linearTester.setMvalues({ 20,30,40,50,60,70,80 });
	linearTester.setCvalues({ 20,30,40,50,60,70,80 });
	linearTester.setTvalues({ 1,2,4,6,8,12,20 });
	linearTester.setGvalues({ 50,100,200,500,1000,2000,5000, 10000 });
	linearTester.setPvalues({ 500, 1250, 2500, 5000, 12500, 25000, 50000 });
	break;
	case 2:
	linearTester.setMvalues({ 20,30,40,50,60,70,80 });
	linearTester.setCvalues({ 20,30,40,50,60,70,80 });
	linearTester.setTvalues({ 1,2,4,6,8,12,20 });
	linearTester.setGvalues({ 5,10,20,50,100,200,500 });
	linearTester.setPvalues({ 50, 120, 250, 500, 1250, 2500, 5000 });
	break;
	}

	vector<string> resultsFileNames = linearTester.testEvolutionAlgorithm(fileNames, fileNumber, fileNumber, 1);*/

	/* DRUGA ITERACJA */
	/*switch (fileNumber) {
	case 0:
	return 0;
	case 1:
	linearTester.setMvalues({ 41,44,47,50,53,56,59 });
	linearTester.setCvalues({ 61,64,67,70,73,76,79 });
	linearTester.setTvalues({ 3,4,5 });
	linearTester.setGvalues({ 500,1000,2000,5000});
	linearTester.setPvalues({ 1250, 2500, 5000,12500,25000});
	break; // max 12,5 godz
	case 2:
	linearTester.setMvalues({ 61,64,67,70,73,76,79 });
	linearTester.setCvalues({ 51,54,57,60,63,66,69 });
	linearTester.setTvalues({ 9,10,11,12,13,14,15 });
	linearTester.setGvalues({ 100,200,500});
	linearTester.setPvalues({ 1250, 2500, 5000});
	break; // max 7,5 godz
	}*/

}

void setParametersForTabuSearch(LinearTester& linearTester, CalculationTime calculationTime, int fileNumber, int iteration) {
	
	if (calculationTime == CalculationTime::Fast) {

		switch (fileNumber) {
		case 0:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,180,190 });
			linearTester.setTivalues({ 100,200,500,1000,2000,5000,10000,20000 });
			break;
		case 1:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,200,300,500,1000 });
			linearTester.setTivalues({ 50,100,200,400,500,600,750 });
			break;
		case 2:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,300,450,1000 });
			linearTester.setTivalues({ 30,50,70,100,150,250 });
			break;
		}

	} else if (calculationTime == CalculationTime::Slow) {

		switch (fileNumber) {
		case 0:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,180,190 });
			linearTester.setTivalues({ 200,500,1000,2000,5000,10000,20000,50000,100000,200000 });
			break;
		case 1:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,5,10,20,50,100,200,500,1000,1250 });
			linearTester.setTivalues({ 400,1000,1600,3000,6000,9000,15000 });
			break;
		case 2:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,5,10,20,50,100,200,500,1000,2000,4000,8000 });
			linearTester.setTivalues({ 30,60,100,200,400,600,1000,2000,3000 });
			break;
		}

	} else if (calculationTime == CalculationTime::VeryFast) {

		switch (fileNumber) {
		case 0:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,180,190 });
			linearTester.setTivalues({ 10,20,50,100,200,500,1000,2000 });
			break;
		case 1:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,200,300,500 });
			linearTester.setTivalues({ 20,30,50,80,120,150,200 });
			break;
		case 2:
			linearTester.setTtvalues({ 1,2,5,10,20,40,60,80,100 });
			linearTester.setTnvalues({ 1,10,30,60,120,150,300,450 });
			linearTester.setTivalues({ 10,15,20,25,30,40 });
			break;
		}

	}

}

void setParametersForSA(LinearTester& linearTester, CalculationTime calculationTime, int fileNumber, int iteration) {

	if (calculationTime == CalculationTime::Fast) {

		switch (fileNumber) {
		case 0:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000,10000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250,500 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,180,190 });
			linearTester.setSivalues({ 100,200,500,1000,2000,5000,10000,20000 });
			break;
		case 1:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,200,300,500,1000 });
			linearTester.setSivalues({ 50,100,200,400,500,600,750 });
			break;
		case 2:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,300,450,1000 });
			linearTester.setSivalues({ 30,50,70,100,150,250 });
			break;
		}

	} else if (calculationTime == CalculationTime::Slow) {

		switch (fileNumber) {
		case 0:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000,10000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250,500 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,180,190 });
			linearTester.setSivalues({ 100,200,500,1000,2000,5000,10000,20000,50000,100000,200000,400000 });
			break;
		case 1:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,200,300,500,1000,1250 });
			linearTester.setSivalues({ 100,200,400,800,1600,3500,5000,10000,20000 });
			break;
		case 2:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,300,450,1000,1500,2000,3000 });
			linearTester.setSivalues({ 60,100,140,200,300,500,800,1200,1500 });
			break;
		}

	} else if (calculationTime == CalculationTime::VeryFast) {

		switch (fileNumber) {
		case 0:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000,10000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250,500 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,180,190 });
			linearTester.setSivalues({ 10,20,50,100,200,500,1000,2000 });
			break;
		case 1:
			linearTester.setS0values({ 2000,5000,10000 });
			//linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,200,300,500 });
			linearTester.setSivalues({ 20,30,50,80,120,150,200 });
			break;
		case 2:
			linearTester.setS0values({ 1,2,5,10,20,50,100,200,500,1000,2000,5000 });
			linearTester.setSvvalues({ 101,105,110,115,120,125,130,150,180,250 });
			linearTester.setSnvalues({ 1,10,30,60,120,150,300,450 });
			linearTester.setSivalues({ 10,15,20,25,30,40 });
			break;
		}

	}

}

void openFileWithExcel2015(string fileName) {
	ShellExecute(nullptr, "open", "C:\\Program Files\\Microsoft Office 15\\root\\office15\\EXCEL.EXE"
		, ("\"C:\\Users\\Adam\\Desktop\\Programming\\Studia\\AlgorytmyGenetyczne\\AlgorytmyGenetyczne\\AlgorytmyGenetyczne\\" + fileName).c_str()
		, "", SW_SHOW);
}

int main() {

	CalculationTime calcTime = CalculationTime::VeryFast;
	MetaheuristicType metaType = MetaheuristicType::SA;
	int repeatTimes = 1;
	int iterationNumber = 1;
	bool executeExcel = false;

	srand(time(nullptr));

	vector<string> fileNames = { "taillard20j5m","taillard50j10m","taillard500j20m" };

	/*int fileNumber = -1;

	while (fileNumber < 0 || fileNumber >= fileNames.size()) {

		cout << "Ktory plik przerobic [0-2] : ";
		cin >> fileNumber;

	}*/

	int neighType = -1;

	while (neighType < 0 || neighType > NeighbourhoodType::Swap16Times) {
		
		cout << "Reposition,ReverseSequence,SwapAll,Swap2Times,Swap4Times,Swap8Times,Swap16Times ? ";
		cin >> neighType;

	}

	LinearTester linearTester;

	linearTester.setExecutionRepeatTimes(repeatTimes);
	linearTester.setNeighType(static_cast<NeighbourhoodType>(neighType));

	vector<string> resultsFileNames;

	for (int fileNumber = 1; fileNumber <= 2; ++fileNumber) {

		switch (metaType) {
		case MetaheuristicType::EvolutionAlgorithms:
			setParametersForEvolutionAlgorithm(linearTester, calcTime, fileNumber, iterationNumber);
			resultsFileNames = linearTester.testEvolutionAlgorithm(fileNames, fileNumber, fileNumber, iterationNumber);
			break;
		case MetaheuristicType::SA:
			setParametersForSA(linearTester, calcTime, fileNumber, iterationNumber);
			resultsFileNames = linearTester.testSA(fileNames, fileNumber, fileNumber, 1);
			break;
		case MetaheuristicType::TabuSearch:
			setParametersForTabuSearch(linearTester, calcTime, fileNumber, iterationNumber);
			resultsFileNames = linearTester.testTabuSearch(fileNames, fileNumber, fileNumber, 1);
			break;
		}

	}

	if (executeExcel) {
		for (int i = 0; i < resultsFileNames.size(); ++i) {
			openFileWithExcel2015(resultsFileNames[i]);
		}
	}

	std::system("pause");

	return 0;

}