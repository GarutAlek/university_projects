#pragma once
#include "Field.h"

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

	void use_field(int x, int y);
	void print_info();

	bool all_coins_collected();

	virtual void move(char way, int count) = 0;
};

// Figure that moves like rook in chess
class Rook : public Unit {
public:
	Rook(Field* field, int x = 0, int y = 0) : Unit(field, x, y) {}
	void move(char way, int count);
};

// Who will use it when Rook is already created? :D
class Tiny_rook : public Unit {
public:
	Tiny_rook(Field* field, int x = 0, int y = 0) : Unit(field, x, y) {}
	void move(char way, int count);
};