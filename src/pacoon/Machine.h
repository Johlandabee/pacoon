#pragma once

#include "Store.h"
#include "Sort.h"

namespace pacoon {
	class Machine {
	public:
		static const int kOutletMin = 20;
		static const int kOutletCount = 10;
		static const int kOutletTolerance = 2;

		Machine(int charges[], const int& size) : store_(charges, size) {
			this->RestockDistributor();
		}

		bool Finished() {
			if (this->store_.Stock() + this->GetDistributorSum() < kOutletMin) return true;

			return false;
		}

		int Stock() {
			return this->store_.Stock();
		}

		int Remnant() {
			return this->remnant_ + this->GetDistributorSum();
		}

		int Pack() {
			int out = 0;
			int next = kOutletMin;

			this->SortDistributor();

			for (size_t i = kOutletCount - 1; i >= 0; --i) {
				if ((this->store_.Stock() == 0) && (this->GetDistributorSum() + out) < kOutletMin) {
					break;
				}

				int d = this->distributor_[i];

				if (d == next || (d > next && d <= (next + kOutletTolerance))) {
					out += this->distributor_[i];
					this->distributor_[i] = this->store_.Pop();

					break;
				} else if (d > (next + kOutletTolerance) && i == 0) {
					this->remnant_ += this->GetDistributorSum();
					this->RestockDistributor();

					break;
				} else if (d < next && d > 0) {
					next -= d;

					out += d;
					this->distributor_[i] = this->store_.Pop();

					this->SortDistributor();
					i = kOutletCount;
				}
			}

			if (out < kOutletMin) {
				this->remnant_ += out;
				out = 0;
			}

			return out;
		}

	private:
		int GetDistributorSum() {
			int total = 0;

			for (size_t i = 0; i < kOutletCount; ++i) {
				total += distributor_[i];
			}

			return total;
		}

		void SortDistributor() {
			pacoon::Sort::QuickSort(this->distributor_, 0, kOutletCount - 1, kOutletCount);
		}

		void RestockDistributor() {
			for (size_t i = 0; i < kOutletCount; ++i)
				this->distributor_[i] = this->store_.Pop();
		}

		pacoon::Store store_;

		int distributor_[kOutletCount];
		int remnant_ = 0;
	};
}