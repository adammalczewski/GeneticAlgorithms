#pragma once
#include <vector>
#include <string>
#include "Statistics.h"

namespace excel {
	
	class Table {
	private:
		std::vector<std::string> _parameters;
		std::vector<std::string> _values;
		std::string _name;

	public:
		
		Table() {}

		Table(const std::vector<std::string>& parameters, const std::vector<std::string>& values, std::string name) {
			_parameters = parameters;
			_values = values;
			_name = name;
		}

		void clearParameters() {
			_parameters.clear();
		}

		void clearValues() {
			_values.clear();
		}

		void addParameter(const std::string& param) {
			_parameters.push_back(param);
		}

		void addValue(const std::string& value) {
			_values.push_back(value);
		}

		void addValues(const std::vector<std::string>& values) {
			for (int i = 0; i < values.size(); ++i) _values.push_back(values[i]);
		}

		const std::vector<std::string>& getParameters() const {
			return _parameters;
		}

		const std::vector<std::string>& getValues() const {
			return _values;
		}

		const std::string& getName() const {
			return _name;
		}

		void setName(const std::string& cs) {
			_name = cs;
		}

		static bool saveToFile(const std::vector <Table> & tables, const std::string& fileName, bool append = true) {

			std::ofstream file;

			std::string tempFileName = fileName + ".tmp";

			file.open(fileName, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

			if (!file.is_open()) return false;

			for (int d = 0; d < tables.size(); ++d) {

				
				file << "[tabela]\n";
				file << "nazwa:\t" << tables[d].getName() << std::endl;
				file << "parametry:\t" << tables[d].getParameters().size() << std::endl;
				for (int p = 0; p < tables[d].getParameters().size(); ++p) file << tables[d].getParameters()[p] << std::endl;
				file << "wartoœci:\t" << tables[d].getValues().size() << "\n";
				for (int v = 0; v < tables[d].getValues().size(); ++v) {
					file << tables[d].getValues()[v] << std::endl;
				}
				file << std::endl;

			}

			file.close();

			return true;

		}

	};

}
