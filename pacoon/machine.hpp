#pragma once

#include "inventory.hpp"
#include "sort.hpp"

namespace pacoon {
	class machine {
	public:
		static const int OUTLET_MIN = 20;
		static const int OUTLET_COUNT = 10;
		static const int OUTLET_TOLERANCE = 2;

		machine(int charges[], const int& size) : _inventory(charges, size) {
			this->rehydrate();
		}

		bool finished() {
			if (this->_inventory.stock() + this->distSum() < OUTLET_MIN) return true;

			return false;
		}

		int stock() {
			return this->_inventory.stock();
		}

		int remnant() {
			return this->_remnant + this->distSum();
		}

		int pack() {
			int out = 0;
			int next = OUTLET_MIN;

			this->sort();

			for (size_t i = OUTLET_COUNT - 1; i >= 0; --i) {
				if ((this->_inventory.stock() == 0) && (this->distSum() + out) < OUTLET_MIN) {
					break;
				}

				int d = this->_distributor[i];

				if (d == next || (d > next && d <= (next + OUTLET_TOLERANCE))) {
					out += this->_distributor[i];
					this->_distributor[i] = this->_inventory.pop();

					break;
				} else if (d > (next + OUTLET_TOLERANCE) && i == 0) {
					this->_remnant += this->distSum();
					this->rehydrate();

					break;
				} else if (d < next && d > 0) {
					next -= d;

					out += d;
					this->_distributor[i] = this->_inventory.pop();

					this->sort();
					i = OUTLET_COUNT;
				}
			}

			if (out < OUTLET_MIN) {
				this->_remnant += out;
				out = 0;
			}

			return out;
		}

	private:
		void sort() {
			pacoon::sort::qsort(this->_distributor, 0, OUTLET_COUNT - 1, OUTLET_COUNT);
		}

		int distSum() {
			int total = 0;

			for (size_t i = 0; i < OUTLET_COUNT; ++i) {
				total += _distributor[i];
			}

			return total;
		}

		void rehydrate() {
			for (size_t i = 0; i < OUTLET_COUNT; ++i) {
				this->_distributor[i] = this->_inventory.pop();
			}
		}

		inventory _inventory;
		int _distributor[OUTLET_COUNT];
		int _remnant = 0;
	};
}