#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "FileUtils.h"

class Statistics;
class AvgAndDevStatistics;

class NamedStatisticsSeries {
public:
	NamedStatisticsSeries(std::vector<Statistics> stats, std::string name) {
		this->stats = stats;
		this->name = name;
	}
	std::vector<Statistics> stats;
	std::string name;
};

class Statistics {
public:
	Statistics(float worstValue, float bestValue, float avgValue, float bestValuePercentage, float deviation) {
		this->worstValue = worstValue;
		this->bestValue = bestValue;
		this->avgValue = avgValue;
		this->bestValuePercentage = bestValuePercentage;
		this->deviation = deviation;
	}
	float worstValue;
	float bestValue;
	float avgValue;
	float bestValuePercentage;
	float deviation;

	static std::vector<Statistics> averageStatistics(std::vector<std::vector<Statistics>> stats) {

		std::vector<Statistics> result;

		for (int i = 0; i < stats[0].size(); ++i) {

			Statistics avgStats(stats[0][i].worstValue, stats[0][i].bestValue, 0.0f,0.0f, 0.0f);

			for (int j = 0; j < stats.size(); ++j) {
				if (avgStats.bestValue > stats[j][i].bestValue) avgStats.bestValue = stats[j][i].bestValue;
				if (avgStats.worstValue < stats[j][i].worstValue) avgStats.worstValue = stats[j][i].worstValue;
				avgStats.avgValue += stats[j][i].avgValue;
				avgStats.bestValuePercentage += stats[j][i].bestValuePercentage;
			}

			avgStats.avgValue /= stats.size();
			avgStats.bestValuePercentage /= stats.size();

			result.push_back(avgStats);

		}

		return result;

	}

	static bool saveGraphToFile(std::vector<NamedStatisticsSeries> stats, std::string fileName, bool comaSeparator = true, bool append = false) {

		std::ofstream file;

		std::string tempFileName = fileName + ".tmp";

		if (comaSeparator) file.open(tempFileName, std::ofstream::out);
		else file.open(fileName, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

		if (!file.is_open()) return false;

		for (int s = 0; s < stats.size(); ++s) {

			file << "[wykres]\t\t\t\t\t\t\t\t\t\t\t\t\t\t[wykres]\n";
			file << "nazwa:\t" << stats[s].name << "\t\t\t\t\t\t\t\t\t\t\t\t\tnazwa:\t" << stats[s].name << " - odchylenie" << std::endl;
			file << "dane:\t" << stats[s].stats.size() << "\t\t\t\t\t\t\t\t\t\t\t\t\tdane:\t" << stats[s].stats.size() << "\n";
			file << "Numer pokolenia\tbest\tworst\tavg\t\t\t\t\t\t\t\t\t\t\tNumer pokolenia\todchylenie\n";

			for (int i = 0; i < stats[s].stats.size(); ++i) {
				file << i + 1 << "\t";
				file << stats[s].stats[i].bestValue << "\t" << stats[s].stats[i].worstValue << "\t"
					<< stats[s].stats[i].avgValue << "\t\t\t\t\t\t\t\t\t\t\t" << i + 1 << "\t" << stats[s].stats[i].deviation << std::endl;
			}
			file << std::endl;

		}

		file.close();

		if (comaSeparator) return files::FileUtils::copyFile(tempFileName, fileName
			, std::vector<files::CharacterChange>({ files::CharacterChange('.',',') }), append);
		else return true;

	}

	static Statistics bestStatistics(std::vector<Statistics> stats) {

		int bestStats = 0;
		int bestBestValue = stats[0].bestValue;

		for (int i = 1; i < stats.size(); ++i) {
			if (stats[i].bestValue < bestBestValue) {
				bestBestValue = stats[i].bestValue;
				bestStats = i;
			}
		}

		return stats[bestStats];

	}

	static bool saveTableToFile(std::vector<std::string> parameters, std::string name, std::string fileName, bool append = true) {

		std::ofstream file;

		file.open(fileName, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

		if (!file.is_open()) return false;

		file << "[tabela]\n";
		file << "nazwa:\t" << name << std::endl;
		file << "parametry:\t" << parameters.size() << std::endl;

		for (int p = 0; p < parameters.size(); ++p) {
			file << parameters[p] << std::endl;
		}

		file << "wartoœci:\t3\n";
		file << "min\n";
		file << "avg\n";
		file << "max\n";
		file << "min (%)\n\n";

		file.close();

		return true;

	}

	static std::vector<std::string> getTableValues() {
		return{ "min","avg","max","min (%)" };
	}

};

inline std::ostream& operator<<(std::ostream& stream, Statistics& stats) {
	return stream << stats.bestValue << " " << stats.worstValue << " " << stats.avgValue;
}

// tylko min avg i max
/*
class Statistics {
public:
	Statistics(float worstValue, float bestValue, float avgValue, float deviation){
		this->worstValue = worstValue;
		this->bestValue = bestValue;
		this->avgValue = avgValue;
		this->deviation = deviation;
	}
	float worstValue;
	float bestValue;
	float avgValue;
	float deviation;

	static std::vector<Statistics> averageStatistics(std::vector<std::vector<Statistics>> stats) {

		std::vector<Statistics> result;

		for (int i = 0; i < stats[0].size(); ++i) {

			Statistics avgStats(stats[0][i].worstValue, stats[0][i].bestValue, 0.0f,0.0f);

			for (int j = 0; j < stats.size(); ++j) {
				if (avgStats.bestValue > stats[j][i].bestValue) avgStats.bestValue = stats[j][i].bestValue;
				if (avgStats.worstValue < stats[j][i].worstValue) avgStats.worstValue = stats[j][i].worstValue;
				avgStats.avgValue += stats[j][i].avgValue;
			}

			avgStats.avgValue /= stats.size();

			result.push_back(avgStats);

		}

		return result;

	}

	static bool saveGraphToFile(std::vector<NamedStatisticsSeries> stats, std::string fileName, bool comaSeparator = true, bool append = false) {
		
		std::ofstream file;

		std::string tempFileName = fileName + ".tmp";

		if (comaSeparator) file.open(tempFileName, std::ofstream::out);
		else file.open(fileName, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

		if (!file.is_open()) return false;

		for (int s = 0; s < stats.size(); ++s) {

			file << "[wykres]\t\t\t\t\t\t\t\t\t\t\t\t\t\t[wykres]\n";
			file << "nazwa:\t" << stats[s].name << "\t\t\t\t\t\t\t\t\t\t\t\t\tnazwa:\t" << stats[s].name << " - odchylenie" << std::endl;
			file << "dane:\t" << stats[s].stats.size() << "\t\t\t\t\t\t\t\t\t\t\t\t\tdane:\t" << stats[s].stats.size() << "\n";
			file << "Numer pokolenia\tbest\tworst\tavg\t\t\t\t\t\t\t\t\t\t\tNumer pokolenia\todchylenie\n";

			for (int i = 0; i < stats[s].stats.size(); ++i) {
				file << i + 1 << "\t";
				file << stats[s].stats[i].bestValue << "\t" << stats[s].stats[i].worstValue << "\t"
					<< stats[s].stats[i].avgValue << "\t\t\t\t\t\t\t\t\t\t\t" << i+1 << "\t" << stats[s].stats[i].deviation << std::endl;
			}
			file << std::endl;

		}

		file.close();

		if (comaSeparator) return files::FileUtils::copyFile(tempFileName, fileName
			, std::vector<files::CharacterChange>({ files::CharacterChange('.',',') }), append);
		else return true;

	}

	static Statistics bestStatistics(std::vector<Statistics> stats) {
		
		int bestStats = 0;
		int bestBestValue = stats[0].bestValue;

		for (int i = 1; i < stats.size();++i) {
			if (stats[i].bestValue < bestBestValue) {
				bestBestValue = stats[i].bestValue;
				bestStats = i;
			}
		}

		return stats[bestStats];

	}

	static bool saveTableToFile(std::vector<std::string> parameters,std::string name, std::string fileName,bool append = true) {
		
		std::ofstream file;

		file.open(fileName, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

		if (!file.is_open()) return false;

		file << "[tabela]\n";
		file << "nazwa:\t" << name << std::endl;
		file << "parametry:\t" << parameters.size() << std::endl;

		for (int p = 0; p < parameters.size();++p) {
			file << parameters[p] << std::endl;
		}

		file << "wartoœci:\t3\n";
		file << "min\n";
		file << "avg\n";
		file << "max\n\n";

		file.close();

		return true;

	}

	static std::vector<std::string> getTableValues() {
		return{ "min","avg","max" };
	}

};

inline std::ostream& operator<<(std::ostream& stream, Statistics& stats) {
	return stream << stats.bestValue << " " << stats.worstValue << " " << stats.avgValue;
}
*/