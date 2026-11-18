#include "include/utils.h"

int getrandom(int start, int end) {
	return (rand() % (end - start) + start);
}
