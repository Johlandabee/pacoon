#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <wincon.h>

namespace pacoon {
	class Helper {
	public:
		
		static bool DoIOwnThisWindow() {
			HWND console = GetConsoleWindow();
			DWORD process;

			GetWindowThreadProcessId(console, &process);

			return GetCurrentProcessId() == process;
		}

		static int Rand(const int& min, const int& max) {
			if (!seeded_) {
				srand(static_cast<int>(time(NULL)));
				seeded_ = true;
			}

			return std::rand() % (max - min) + min;
		}

		static void RandPopulateIntVector(std::vector<int>* vec, const int& count, const int& min, const int& max) {
			for (int i = 0; i < count; ++i)
				vec->insert(vec->end(), pacoon::Helper::Rand(min, max));
		}

		static void IntVectorFromFile(const char* file, std::vector<int>* vec) {
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

		static void PrintIntArray(int* arr, const int& size, const char& seperator = ',') {
			for (int i = 0; i < size; ++i) {
				std::cout << arr[i];
				if (i < size - 1) std::cout << seperator;
			}

			std::cout << std::endl;
		}

	private:
		static bool seeded_;
	};

	bool pacoon::Helper::seeded_ = false;
}