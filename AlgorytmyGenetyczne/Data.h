#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "FileUtils.h"
#include "NamedValue.h"

namespace excel {
	
	class Data {
	private:
		std::vector<NamedValue> _parameters;
		std::vector<NamedValue> _values;

	public:

		Data(){}

		//puts values from Statistics object to _values vector
		explicit Data(const Statistics& statistics) {
			_values.push_back(NamedValue("min", static_cast<int>(statistics.bestValue)));
			_values.push_back(NamedValue("avg", static_cast<int>(statistics.avgValue)));
			_values.push_back(NamedValue("max", static_cast<int>(statistics.worstValue)));
			_values.push_back(NamedValue("min (%)", static_cast<int>(statistics.bestValuePercentage)));
		}

		Data(const std::vector<NamedValue>& parameters,const std::vector<NamedValue>& values) {
			_parameters = parameters;
			_values = values;
		}
		
		void clearParameters() {
			_parameters.clear();
		}

		void clearValues() {
			_values.clear();
		}

		void addParameter(const NamedValue& param) {
			_parameters.push_back(param);
		}

		void addValue(const NamedValue& value) {
			_values.push_back(value);
		}


		const std::vector<NamedValue>& getParameters() const {
			return _parameters;
		}

		const std::vector<NamedValue>& getValues() const {
			return _values;
		}

		static bool saveToFile(const std::vector<Data>& data,const std::string& fileName, bool comaSeparator = true, bool append = true) {

			std::ofstream file;

			std::string tempFileName = fileName + ".tmp";

			if (comaSeparator) file.open(tempFileName, std::ofstream::out);
			else file.open(fileName, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

			if (!file.is_open()) return false;

			for (int d = 0; d < data.size(); ++d) {

				file << "[dane]\n";
				file << "parametry:\t" << data[d].getParameters().size() << std::endl;
				for (int p = 0; p < data[d].getParameters().size(); ++p) file << data[d].getParameters()[p].name << "\t"
					<< data[d].getParameters()[p].value << std::endl;
				file << "wartoœci:\t" << data[d].getValues().size() << "\n";
				for (int v = 0; v < data[d].getValues().size(); ++v) file << data[d].getValues()[v].name << "\t"
					<< data[d].getValues()[v].value << "\n";
				file << "\n";

			}

			file.close();

			if (comaSeparator) return files::FileUtils::copyFile(tempFileName, fileName
				, std::vector<files::CharacterChange>({ files::CharacterChange('.',',') }), append);
			else return true;

		}

	};

}
