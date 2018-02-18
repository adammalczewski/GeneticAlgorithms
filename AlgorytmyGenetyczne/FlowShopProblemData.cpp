#include "FlowShopProblemData.h"

#include <fstream>

using namespace std;

ProblemData<FlowShopProblem>::ProblemData() {
	_executionTimes = nullptr;
	_jobsCount = 0;
	_machinesCount = 0;
}


ProblemData<FlowShopProblem>::~ProblemData() {
	if (_executionTimes != nullptr) {
		for (int i = 0; i < _machinesCount; ++i) delete [] _executionTimes[i];
		delete [] _executionTimes;
	}
}

/* FILE STRUCTURE
[number of machines]
[number of jobs]
[time of executing 1st job on 1st machine] [2nd job on 1st machine] ...
[time of executing 1st job on 2nd machine] [2nd job on 2nd machine] ...
...
*/
void ProblemData<FlowShopProblem>::loadFromFile(std::string fileName) {

	ifstream file;

	file.open(fileName.c_str(), fstream::in);

	file >> _machinesCount;
	file >> _jobsCount;

	_executionTimes = new int*[_machinesCount]; 
	for (int i = 0; i < _machinesCount; ++i) _executionTimes[i] = new int[_jobsCount];

	for (int m = 0; m < _machinesCount;++m)
	for (int j = 0; j < _jobsCount; ++j){
		file >> _executionTimes[m][j];
	}

	file.close();

}