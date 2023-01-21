#include "Field.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include "Source.cpp"

using namespace std;



Field::Field(int size_x, int size_y) {
	this->width = size_x;
	this->heigth = size_y;
	this->field = new char* [size_y];
	for (int i = 0; i < size_y; i++) {
		this->field[i] = new char[size_x];
	}
	fill_field();
}

void Field::fill_field() {
	int rnd;
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			rnd = rand() % 100;
			if (rnd < 50)
				field[i][j] = '_'; // nothing
			else if (rnd < 70)
				field[i][j] = '0'; // wall
			else if (rnd < 83) {
				field[i][j] = '$'; // coin
				if (i != 0 or j != 0) //  else always will be coin at the start
					coins_coords.push_back(coords(j, i));
			}
			else if (rnd < 95)
				field[i][j] = '*'; // trap
			else
				field[i][j] = '+'; // heal
		}
	}
	field[0][0] = '_'; // we always will start here, so it shouldn't be smth
}

void Field::print(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			if (i == y && j == x) {
				SetConsoleTextAttribute(hConsole, 9);
				cout << "#" << " "; // player
			}
			else {
				switch (field[i][j])
				{
				case '_':
					SetConsoleTextAttribute(hConsole, 11);
					cout << field[i][j] << " ";
					break;
				case '0':
					SetConsoleTextAttribute(hConsole, 8);
					cout << field[i][j] << " ";
					break;
				case '$':
					SetConsoleTextAttribute(hConsole, 14);
					cout << field[i][j] << " ";
					break;
				case '*':
					SetConsoleTextAttribute(hConsole, 2);
					cout << field[i][j] << " ";
					break;
				case '+':
					SetConsoleTextAttribute(hConsole, 12);
					cout << field[i][j] << " ";
					break;
				default:
					break;
				}
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
}

bool Field::can_move(int x, int y) {
	if (x < 0 or y < 0 or x >= width or y >= heigth)
		return false;
	return field[y][x] != '0';
}

char Field::get_element(int x, int y) {
	if (not (x < 0 or y < 0 or x >= width or y >= heigth))
		return field[y][x];
	return -1; // some error
}

void Field::collect_coin(int x, int y) {
	if (get_element(x, y) == '$') {
		field[y][x] = '_';
		for (int i = 0; i < coins_coords.size(); i++)
			if (coins_coords[i].x == x and coins_coords[i].y == y)
				coins_coords.erase(coins_coords.begin() + i);
	}
}

void Field::collect_medkit(int x, int y) {
	if (get_element(x, y) == '+') 
		field[y][x] = '_';
}

int Field::weight(int x, int y) {
	switch (field[y][x])
	{
	case '_':
		return 5;
	case '$':
		return 1;
	case '*':
		return 30;
	case '+':
		return 1;
	case '0':
		return -1;
	default:
		return -1;
	}
}

coords Field::coin_coords() {
	srand(time(0));
	return coins_coords[rand() % coins_coords.size()];
}

