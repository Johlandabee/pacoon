#pragma once

#include <algorithm>

namespace pacoon {
	class sort {
	public:
		static void qsort(int arr[], const int& left, const int& right, const int& size) {
			if (left >= right) return;

			int part = pacoon::sort::partition(arr, left, right);

			pacoon::sort::qsort(arr, left, part - 1, size);
			pacoon::sort::qsort(arr, part + 1, right, size);
		}

	private:
		static int partition(int arr[], const int& left, const int& right) {
			const int mid = left + (right - left) / 2;
			const int pivot = arr[mid];

			std::swap(arr[mid], arr[left]);
			int i = left + 1;
			int j = right;

			while (i <= j) {
				while (i <= j && arr[i] <= pivot) {
					i++;
				}

				while (i <= j && arr[j] > pivot) {
					j--;
				}

				if (i < j) {
					std::swap(arr[i], arr[j]);
				}
			}

			std::swap(arr[i - 1], arr[left]);
			return i - 1;
		}
	};
}