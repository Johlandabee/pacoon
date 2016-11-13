#pragma once

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <vector>

#include "helper.hpp"
#include "machine.hpp"

int main(int argc, char** argv) {
	std::cout << "pacoon 1.0.0 - Packin' your balloons since 2016" << std::endl << std::endl;

	const int OUT_WIDTH = 20;

	bool debug = false;

	char* file = "";
	bool fromFile = false;

	int inventorySize = 1000;
 
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
				

				inventorySize = std::stoi(argv[i + 1]);
			}
		}
	}
	catch (const std::logic_error e) {
		std::cout << e.what() << std::endl;

		return 1;
	}

	std::vector<int> inventory;

	if (fromFile) {
		std::cout << "Loading list from file: " << file << std::endl;

		try {
			pacoon::helper::intVectorFromFile(file, &inventory);
		}
		catch (std::logic_error e) {
			std::cout << e.what() << std::endl;

			return 1;
		}
	} else {
		std::cout << "Creating random array with " << inventorySize << " values..." << std::endl;

		pacoon::helper::randPopulateIntVector(&inventory, inventorySize, 1, 15);
	}

	if (debug) {
		std::cout << "Inventory: " << std::endl << std::endl;
		pacoon::helper::printIntArray(&inventory[0], inventory.size());
		std::cout << std::endl;
	}


	int total = 0;
	for (size_t i = 0; i < inventory.size(); ++i){
		total += inventory[i];
	}

	std::cout << std::setfill('.') << std::setw(OUT_WIDTH) << std::left << "Total:" << std::right << total << std::endl << std::endl;

	pacoon::machine machine(&inventory[0], inventory.size());

	double packages = 0;
	double balloons = 0;

	while (!machine.finished()) {
		int package = machine.pack();

		if (package > 0) {
			balloons += package;
			++packages;

			if (debug) std::cout << "Package-No:" << packages << " Balloons:" << package << " Stock:" << machine.stock() << " Remnant:" << machine.remnant() << std::endl;
		}
	}

	double average = balloons / packages;

	std::cout << std::endl << "Result:" << std::endl << std::endl;
	std::cout << std::setfill('.') << std::setw(OUT_WIDTH) << std::left << "Balloons:" << std::right << balloons << std::endl;
	std::cout << std::setfill('.') << std::setw(OUT_WIDTH) << std::left << "Packages:" << std::right << packages << std::endl;
	std::cout << std::setfill('.') << std::setw(OUT_WIDTH) << std::left << "Remnant:" << std::right << machine.remnant() << std::endl;
	std::cout << std::setfill('.') << std::setw(OUT_WIDTH) << std::left << "Average:" << std::right << average << std::endl;

	if (debug) {
		std::cout << std::endl << "Press return to exit." << std::endl;
		std::cin.ignore();
	}	

	std::cout << std::endl << std::endl;

	return 0;
}