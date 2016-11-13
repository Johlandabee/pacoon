#pragma once

namespace pacoon {
	class inventory {
	public:
		inventory(int charges[], const int& size) {
			this->_charges = charges;
			this->_size = size;

			count();
		}

		int stock() {
			return _total - _fetched;
		}

		int pop() {
			int charge = this->_current < this->_size ? _charges[this->_current++] : 0;
			this->_fetched += charge;

			return charge;
		}

	private:
		void count() {
			for (int i = 0; i < _size; ++i)
				this->_total += this->_charges[i];
		}

		int* _charges = nullptr;

		int _size = 0, _total = 0, _current = 0, _fetched = 0;
	};
}