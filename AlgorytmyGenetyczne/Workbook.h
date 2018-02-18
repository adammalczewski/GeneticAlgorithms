#pragma once
#include "Statistics.h"
#include "Data.h"
#include "Table.h"

namespace excel {

	class Workbook {
	private:
		std::vector<NamedStatisticsSeries> _graphs;
		std::vector<Data> _data;
		std::vector<Table> _tables;
	public:

		void clearGraphs() {
			_graphs.clear();
		}

		void clearData() {
			_data.clear();
		}

		void clearTables() {
			_tables.clear();
		}

		void addGraph(const NamedStatisticsSeries& graph) {
			_graphs.push_back(graph);
		}

		void addData(const Data& data) {
			_data.push_back(data);
		}

		void addTable(const Table& table) {
			_tables.push_back(table);
		}

		bool saveToFile(const std::string& fileName, bool comaSeparator) const {

			
			if (!Statistics::saveGraphToFile(_graphs, fileName, comaSeparator, false)) return false;

			if (!Data::saveToFile(_data, fileName, comaSeparator, true)) return false;

			if (!Table::saveToFile(_tables, fileName, true)) return false;

			return true;

		}

	};

}
