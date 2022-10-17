#include "Approach.h"
int Approach::factorial(int num) {
	if (num <= 1) { return 1; }
	return num * factorial(num - 1);
}
