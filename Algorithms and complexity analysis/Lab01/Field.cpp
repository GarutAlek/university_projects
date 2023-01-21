#include "Field.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>

using namespace std;

Field::Field(int size_x, int size_y) {
	this->width = size_x;
	this->heigth = size_y;
	this->field = new char* [size_y];
	this->coins_count = 0;
	for (int i = 0; i < size_y; i++) {
		this->field[i] = new char[size_x];
	}
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
				coins_count++;
			}
			else if (rnd < 95)
				field[i][j] = '*'; // trap
			else
				field[i][j] = '+'; // heal
		}
	}
	if (field[0][0] == '$')
		coins_count--;
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
		coins_count--;
	}
}

void Field::collect_medkit(int x, int y) {
	if (get_element(x, y) == '+') 
		field[y][x] = '_';
}