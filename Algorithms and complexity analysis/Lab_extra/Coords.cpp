#include <math.h>

struct coords {
	int x;
	int y;
	coords(int x, int y) {
		this->x = x;
		this->y = y;
	}
	float dist(coords point) {
		return sqrt(pow(abs(x - point.x), 2) + pow(abs(y - point.y), 2));
	}
};