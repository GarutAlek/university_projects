#include "Unit.h"
#include <iostream>
#include <windows.h>

using namespace std;

void Unit::use_field(int x, int y) {
	switch (field->get_element(x, y))
	{
	case '$':
		field->collect_coin(x, y);
		score++;
		break;
	case '*':
		hp--;
		break;
	case '+':
		if (hp < 5) {
			hp++;
			field->collect_medkit(x, y);
		}
		break;
	default:
		break;
	}
}

void Unit::print_info() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Your score: ";
	SetConsoleTextAttribute(hConsole, 14);
	cout << score << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Your HP: ";
	SetConsoleTextAttribute(hConsole, 10);
	cout << hp << endl;
	SetConsoleTextAttribute(hConsole, 15);
}

void Rook::move(char way, int count) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int dx = 0;
	int dy = 0;
	bool check = true;

	if (count < 0) {
		cout << endl;
		cout << "Hello, my name is Program" << endl;
		SetConsoleTextAttribute(hConsole, 12);
		Sleep(1500);
		cout << "and I HAAATE NEGATIVE NUMBERS" << endl;
		SetConsoleTextAttribute(hConsole, 14);
		Sleep(1500);
		cout << "SEE YOU LATER, sussy baka who dares to enter a negative number" << endl;
		SetConsoleTextAttribute(hConsole, 15);
		exit(0);
	}

	switch (way)
	{
	case 'w':
		dy = -count;
		for (int i = y; i >= y + dy; i--) {
			check = field->can_move(x, i);
			if (not check) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "STOP! NOT SO FAST, you can't move here" << endl;
				break;
			}
		}
		break;
	case 's':
		dy = count;
		for (int i = y; i <= y + dy; i++) {
			check = field->can_move(x, i);
			if (not check) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "STOP! NOT SO FAST, you can't move here" << endl;
				break;
			}
		}
		break;
	case 'd':
		dx = count;
		for (int i = x; i <= x + dx; i++) {
			check = field->can_move(i, y);
			if (not check) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "STOP! NOT SO FAST, you can't move here" << endl;
				break;
			}
		}
		break;
	case 'a':
		dx = -count;
		for (int i = x; i >= x + dx; i--) {
			check = field->can_move(i, y);
			if (not check) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "STOP! NOT SO FAST, you can't move here" << endl;
				break;
			}
		}
		break;
	default:
		cout << "Incorrect dirrection" << endl;
		break;
	}
	if (check) {
		switch (way)
		{
		case 'w':
			for (int i = y; i >= y + dy; i--) {
				use_field(x, i);
			}
			break;
		case 's':
			for (int i = y; i <= y + dy; i++) {
				use_field(x, i);
			}
			break;
		case 'a':
			for (int i = x; i >= x + dx; i--) {
				use_field(i, y);
			}
			break;
		case 'd':
			for (int i = x; i <= x + dx; i++) {
				use_field(i, y);
			}
			break;
		default:
			break;
		}
	}
	if (check) {
		x += dx;
		y += dy;
	}
}

// count is useless here
void Tiny_rook::move(char way, int count) {
	int dx = 0;
	int dy = 0;
	switch (way)
	{
	case 'w':
		dy--;
		break;
	case 's':
		dy++;
		break;
	case 'd':
		dx++;
		break;
	case 'a':
		dx--;
		break;
	default:
		cout << "Incorrect dirrection" << endl;
		break;
	}
	if (field->can_move(x + dx, y + dy)) {
		use_field(x + dx, y + dy);
		x += dx;
		y += dy;
	}
}

bool Unit::all_coins_collected() {
	return field->all_coins_collected();
}