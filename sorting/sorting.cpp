#include "sorting.h"

void __declspec(dllexport) __stdcall sort(int* data, int len) {
	for (int i = 0; i < len; i++) {
		int* min = data + i;

		for (int k = i; k < len; k++) {
			if (*(data + k) < *min) { min = data + k; }
		}

		int tmp = *(data + i);
		*(data + i) = *min;
		*min = tmp;
	}
}
