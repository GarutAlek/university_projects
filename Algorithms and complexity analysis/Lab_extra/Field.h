#pragma once
#include <iostream>
#include "Coords.cpp"
#include <conio.h>

using namespace std;

class Field
{
private:
	char** field;

	int width;
	int heigth;

public:
	Field(int size_x, int size_y, coords start_pos);

	int get_width() { return width; }
	int get_heigth() { return heigth; }

	void fill_field(coords start_pos);
	void print(coords pos, float vision_range);

	bool chop_tree(coords tree);

	//bool can_move(coords point) { return on_field(point) and field[point.y][point.x] != 'T' and field[point.y][point.x] != 'R'; }
	char get_element(coords point) { return field[point.y][point.x]; }

	bool on_field(coords point) { return not (point.x < 0 or point.y < 0 or point.x >= width or point.y >= heigth); }
};

