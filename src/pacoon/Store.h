#pragma once

namespace pacoon {
	class Store {
	public:
		Store(int charges[], const int& size) {
			this->charges_ = charges;
			this->size_ = size;

			Count();
		}

		int Stock() {
			return total_ - fetched_;
		}

		int Pop() {
			int charge = this->current_ < this->size_ ? charges_[this->current_++] : 0;
			this->fetched_ += charge;

			return charge;
		}

	private:
		void Count() {
			for (int i = 0; i < size_; ++i)
				this->total_ += this->charges_[i];
		}

		int* charges_ = nullptr;

		int size_ = 0, total_ = 0, current_ = 0, fetched_ = 0;
	};
}