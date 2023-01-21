#include "Field.h"
#include <windows.h>

Field::Field(int size_x, int size_y, coords start_pos) {
	this->width = size_x;
	this->heigth = size_y;
	this->field = new char* [size_y];
	for (int i = 0; i < size_y; i++) {
		this->field[i] = new char[size_x];
	}
	fill_field(start_pos);
}

void Field::fill_field(coords start_pos) {
	int rnd;
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			rnd = rand() % 100;
			if (rnd < 70)
				field[i][j] = '_'; // nothing
			else if (rnd < 85)
				field[i][j] = 'R'; // ROCK AND STONE!!
			else
				field[i][j] = 'T'; // tree
		}
	}
	field[start_pos.y][start_pos.x] = '_'; // we will start here, so it shouldn't be smth
}

void Field::print(coords pos, float vision_range) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = pos.y - vision_range; i <= pos.y + vision_range; i++) {
		for (int j = pos.x - vision_range; j <= pos.x + vision_range; j++) {
			if (i == pos.y and j == pos.x) {
				SetConsoleTextAttribute(hConsole, 13);
				cout << "&"; // player
			}
			else
				if (pos.dist(coords(j, i)) > vision_range)
					cout << " "; // player can't see this
				else
					if (i < 0 or j < 0 or i >= heigth or j >= width) {
						SetConsoleTextAttribute(hConsole, 7);
						cout << "#"; // not on map
					}
					else {
						if (field[i][j] == 'T')
							SetConsoleTextAttribute(hConsole, 10);
						else if (field[i][j] == 'R')
							SetConsoleTextAttribute(hConsole, 1);
						else
							SetConsoleTextAttribute(hConsole, 8);
						cout << field[i][j]; // player see this
					}
			cout << " ";
		}
		cout << endl;
	}
}

bool Field::chop_tree(coords tree) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Chop tree? Y - yes, N - no" << endl;
	char answer;
	answer = _getch();
	if (answer == 'y' or answer == 'Y') {
		cout << "chop - chop" << endl;
		Sleep(1000);
		cout << "BYYYEE, TREEEEE!" << endl;
		Sleep(1000);
		field[tree.y][tree.x] = '_';
		return true;
	}
	return false;
}