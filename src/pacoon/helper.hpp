#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <exception>
#include <string>
#include <vector>

namespace pacoon {
	class helper {
	public:
		static int rand(const int& min, const int& max) {
			if (!seeded) {
				srand(static_cast<int>(time(NULL)));
				seeded = true;
			}

			return std::rand() % (max - min) + min;
		}

		static void randPopulateIntVector(std::vector<int>* vec, const int& count, const int& min, const int& max) {
			for (int i = 0; i < count; ++i)
				vec->insert(vec->end(), pacoon::helper::rand(min, max));
		}

		static void intVectorFromFile(const char* file, std::vector<int>* vec) {
			std::ifstream fs(file);
			if (fs.good()) {
				std::string line;

				while (std::getline(fs, line)) {
					vec->insert(vec->end(), std::stoi(line.c_str()));
				}
			}
			else {
				throw std::logic_error("Could not read file");
			}
		}

		static void printIntArray(int* arr, const int& size, const char& seperator = ',') {
			for (int i = 0; i < size; ++i) {
				std::cout << arr[i];
				if (i < size - 1) std::cout << seperator;
			}

			std::cout << std::endl;
		}

	private:
		static bool seeded;
	};

	bool pacoon::helper::seeded = false;
}