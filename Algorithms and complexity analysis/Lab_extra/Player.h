#pragma once
#include <iostream>
//#include "Coords.cpp"
#include "Field.h"

class Player
{
private:
	coords pos = coords(0, 0);
	float vision_range;

	Field* field;

public:
	Player(int x, int y, float vision_range, Field* field) { this->vision_range = vision_range; this->pos = coords(x, y); this->field = field; }

	coords get_pos() { return pos; }
	float get_vis() { return vision_range; }

	void move(char way);
};

