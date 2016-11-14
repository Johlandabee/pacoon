#pragma once

#include <Windows.h>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "helper.h"
#include "machine.h"

int main(int argc, char** argv) {
	SetConsoleTitle("pacoon 1.0.0");

	std::cout << "pacoon 1.0.0 - Packin' your balloons since 2016" << std::endl << std::endl;

	const int kOutWidth = 20;

	bool debug = false;

	char* file = "";
	bool fromFile = false;

	int storeSize = 1000;
	
	// Parsing command line arguments.
	try {
		for (int i = 0; i < argc; ++i) {
			if (std::strcmp(argv[i], "-debug") == 0)
				debug = true;
			

			if (std::strcmp(argv[i], "-file") == 0) {
				if ((i + 1) >= argc || (std::strstr(argv[i + 1], ".txt") == nullptr) || fromFile)
					throw std::logic_error("Invalid parameters");
				
				file = argv[i + 1];
				fromFile = true;
			}

			if (std::strcmp(argv[i], "-random") == 0) {
				if ((i + 1) >= argc)
					throw std::logic_error("Invalid parameters");
				

				storeSize = std::stoi(argv[i + 1]);
			}
		}
	}
	catch (const std::logic_error e) {
		std::cout << e.what() << std::endl;

		return 1;
	}

	// Setting up a store containing all our values.
	std::vector<int> store;

	if (fromFile) {
		std::cout << "Loading list from file: " << file << std::endl;

		try {
			// Parsing a integer list from file.
			pacoon::Helper::IntVectorFromFile(file, &store);
		}
		catch (std::logic_error e) {
			std::cout << e.what() << std::endl;

			return 1;
		}
	} else {
		std::cout << "Creating random array with " << storeSize << " values..." << std::endl;

		// Randomly populating our list with n values.
		pacoon::Helper::RandPopulateIntVector(&store, storeSize, 1, 15);
	}

	if (debug) {
		// Printing all store values.
		std::cout << "Store: " << std::endl << std::endl;
		pacoon::Helper::PrintIntArray(&store[0], store.size());
		std::cout << std::endl;
	}

	// Calculating and printing the sum of all values within the store.
	int total = 0;
	for (size_t i = 0; i < store.size(); ++i){
		total += store[i];
	}

	std::cout << std::setfill('.') << std::setw(kOutWidth) << std::left << "Total:" << std::right << total << std::endl << std::endl;

	// Crating "balloon machine" instance and passing our previously created values.
	pacoon::Machine machine(&store[0], store.size());

	double packages = 0; // Packages packed my our machine
	double balloons = 0; // Balloons packed
	
	// Run our machine until finished meaning until we're out of balloons 
	while (!machine.Finished()) {
		int package = machine.Pack();

		// Counting packages:
		// If pack could not crate a package within the limits i.e. >= 20 && <= 20 + tolerance,
		// it will return 0 and the package will be discarded respectively added to our remnant.
		if (package > 0) {
			balloons += package;
			++packages;

			// Additional debug output for each package successfully created.
			if (debug) std::cout << "Package-No:" << packages << " Balloons:" << package << " Stock:" << machine.Stock() << " Remnant:" << machine.Remnant() << std::endl;
		}
	}

	// Calculating average balloons per package.
	double average = balloons / packages;

	// Printing results.
	std::cout << std::endl << "Result:" << std::endl << std::endl;
	std::cout << std::setfill('.') << std::setw(kOutWidth) << std::left << "Balloons:" << std::right << balloons << std::endl;
	std::cout << std::setfill('.') << std::setw(kOutWidth) << std::left << "Packages:" << std::right << packages << std::endl;
	std::cout << std::setfill('.') << std::setw(kOutWidth) << std::left << "Remnant:" << std::right << machine.Remnant() << std::endl;
	std::cout << std::setfill('.') << std::setw(kOutWidth) << std::left << "Average:" << std::right << average << std::endl;

	// Wait for input if not called from command line.
	if (pacoon::Helper::DoIOwnThisWindow()) {
		std::cout << std::endl << "Press return to exit." << std::endl;
		std::cin.ignore();
	}	

	std::cout << std::endl << std::endl;

	return 0;
}