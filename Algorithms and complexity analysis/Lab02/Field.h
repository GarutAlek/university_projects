#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Source.cpp"

using namespace std;

class Field
{
private:
	char** field;

	int width;
	int heigth;

	vector<coords> coins_coords;

public:
	Field(int size_x, int size_y);

	int get_width() { return width; }
	int get_heigth() { return heigth; }

	int weight(int x, int y);
	coords coin_coords();

	void fill_field();
	void print(int x, int y);

	bool can_move(int x, int y);
	char get_element(int x, int y);
	void collect_coin(int x, int y);
	void collect_medkit(int x, int y);
	bool all_coins_collected() { return coins_coords.size() == 0; }
	bool on_field(int x, int y) { return not (x < 0 or y < 0 or x >= width or y >= heigth); }
};

