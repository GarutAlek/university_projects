#pragma once

struct way {
public:
	char dir;
	int count;
	way(char dir, int count) {
		this->dir = dir;
		this->count = count;
	}
};

struct coords {
public:
	int x;
	int y;
	coords(int x, int y) {
		this->x = x;
		this->y = y;
	}
};