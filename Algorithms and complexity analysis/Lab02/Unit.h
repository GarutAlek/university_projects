#pragma once
#include "Field.h"
#include <string>
#include <vector>
#include <iostream>
#include <iostream>
#include "Source.cpp"

using namespace std;

class Unit
{
protected:
	int x;
	int y;
	int hp = 5; // our max hp is 5
	int score = 0;
	Field* field;

public:
	Unit(Field* field, int x = 0, int y = 0) { this->field = field; this->x = x; this->y = y; }

	int get_x() { return x; }
	int get_y() { return y; }

	bool is_alive() { return hp > 0; }
	int get_score() { return score; }

	void use_field(coords point);
	void print_info();

	virtual void move(char way, int count) = 0;

	virtual vector<coords> children(coords parent) = 0;

	vector<way> shortest_way(coords start, coords finish);
};

// Figure that moves like rook in chess
class Rook : public Unit {
public:
	Rook(Field* field, int x = 0, int y = 0) : Unit(field, x, y) {}
	void move(char way, int count);
	vector<coords> children(coords parent);
};

// Who will use it when Rook is already created? :D
class Tiny_rook : public Unit {
public:
	Tiny_rook(Field* field, int x = 0, int y = 0) : Unit(field, x, y) {}
	void move(char way, int count);
	vector<coords> children(coords parent);
};