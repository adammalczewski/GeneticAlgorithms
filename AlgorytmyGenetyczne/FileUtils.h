#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace files {

	class CharacterChange {
	public:
		char from;
		char to;
		CharacterChange(char from, char to)
			: from(from),
			to(to) {
		}
	};

	class FileUtils {
	public:

		static bool copyFile(const std::string& sourceFile, const std::string& destFile, const std::vector<CharacterChange> changes, bool append = false) {

			std::ofstream fileOut;
			std::ifstream fileIn;

			fileIn.open(sourceFile, std::ifstream::in);
			fileOut.open(destFile, (append) ? (std::ofstream::out | std::ofstream::app) : std::ofstream::out);

			if (!fileIn.is_open() || !fileOut.is_open()) {
				if (fileIn.is_open()) fileIn.close();
				if (fileOut.is_open()) fileOut.close();
				return false;
			}

			std::string line;

			while (std::getline(fileIn, line)) {

				for (int i = 0; i < line.size(); ++i) {
					if (line[i] == '.') line[i] = ',';
				}

				fileOut << line << std::endl;

			}

			fileIn.close();
			fileOut.close();

			return true;

		}

	};

}