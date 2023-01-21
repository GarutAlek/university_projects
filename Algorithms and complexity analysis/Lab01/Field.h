#pragma once
class Field
{
private:
	char** field;
	int width;
	int heigth;
	int coins_count;

public:
	Field(int size_x, int size_y);
	void fill_field();
	void print(int x, int y);

	bool can_move(int x, int y);
	char get_element(int x, int y);
	void collect_coin(int x, int y);
	void collect_medkit(int x, int y);
	bool all_coins_collected() { return coins_count == 0; } // I hope it always be >=0 :))
};

