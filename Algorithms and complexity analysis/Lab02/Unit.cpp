#include "Unit.h"
#include "Field.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include "Source.cpp"

using namespace std;

void Unit::use_field(coords point) {
	switch (field->get_element(point.x, point.y))
	{
	case '$':
		field->collect_coin(point.x, point.y);
		score++;
		break;
	case '*':
		hp--;
		break;
	case '+':
		if (hp < 5) {
			hp++;
			field->collect_medkit(point.x, point.y);
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
				use_field(coords(x, i));
			}
			break;
		case 's':
			for (int i = y; i <= y + dy; i++) {
				use_field(coords(x, i));
			}
			break;
		case 'a':
			for (int i = x; i >= x + dx; i--) {
				use_field(coords(i, y));
			}
			break;
		case 'd':
			for (int i = x; i <= x + dx; i++) {
				use_field(coords(i, y));
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
		use_field(coords(x + dx, y + dy));
		x += dx;
		y += dy;
	}
}

vector<coords> Tiny_rook::children(coords parent) {
	vector<coords> res;
	if (field->can_move(parent.x + 1, parent.y))
		res.push_back(coords(parent.x + 1, parent.y));
	if (field->can_move(parent.x - 1, parent.y))
		res.push_back(coords(parent.x - 1, parent.y));
	if (field->can_move(parent.x, parent.y + 1))
		res.push_back(coords(parent.x, parent.y + 1));
	if (field->can_move(parent.x, parent.y - 1))
		res.push_back(coords(parent.x, parent.y - 1));
	return res;
}

vector<coords> Rook::children(coords parent) {
	vector<coords> res;
	int i = 1;
	while (field->can_move(parent.x + i, parent.y)) {
		res.push_back(coords(parent.x + i, parent.y));
		i++;
	}
	i = 1;
	while (field->can_move(parent.x - i, parent.y)) {
		res.push_back(coords(parent.x - i, parent.y));
		i++;
	}
	i = 1;
	while (field->can_move(parent.x , parent.y + i)) {
		res.push_back(coords(parent.x, parent.y + i));
		i++;
	}
	i = 1;
	while (field->can_move(parent.x, parent.y - i)) {
		res.push_back(coords(parent.x, parent.y - i));
		i++;
	}
	return res;
}

vector<way> Unit::shortest_way(coords start, coords finish) {
	int h = field->get_heigth();
	int w = field->get_width();
	int** astar = new int* [h];
	for (int i = 0; i < h; i++) {
		astar[i] = new int[w];
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (field->weight(j, i) == -1)
				astar[i][j] = -1;
			else
				astar[i][j] = -2;
		}
	}
	astar[finish.y][finish.x] = 0;
	bool fl = true;
	while (fl) {
		fl = false;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (i > 0) {
					if (astar[i - 1][j] >= 0 && (astar[i - 1][j] + field->weight(j, i) < astar[i][j] or astar[i][j] == -2)) {
						astar[i][j] = astar[i - 1][j] + field->weight(j, i);
						fl = true;
					}
				}
				if (j > 0) {
					if (astar[i][j - 1] >= 0 && (astar[i][j - 1] + field->weight(j, i) < astar[i][j] or astar[i][j] == -2)) {
						astar[i][j] = astar[i][j - 1] + field->weight(j, i);
						fl = true;
					}
				}
				if (i < h - 1) {
					if (astar[i + 1][j] >= 0 && (astar[i + 1][j] + field->weight(j, i) < astar[i][j] or astar[i][j] == -2)) {
						astar[i][j] = astar[i + 1][j] + field->weight(j, i);
						fl = true;
					}
				}
				if (j < w - 1) {
					if (astar[i][j + 1] >= 0 && (astar[i][j + 1] + field->weight(j, i) < astar[i][j] or astar[i][j] == -2)) {
						astar[i][j] = astar[i][j + 1] + field->weight(j, i);
						fl = true;
					}
				}
			}
		}
	}
	vector<way> res;
	if (astar[start.y][start.x] < 0) {
		res.push_back(way('q', 0));
		return res;
	}
	//vector<way> res;
	coords now = start;
	vector<coords> neighbours;
	coords min_n(0,0);
	int min_neigh;
	while (now.x != finish.x or now.y != finish.y) {
		neighbours = children(now);
		min_neigh = 10000;
		for (int i = 0; i < neighbours.size(); i++) {
			if (astar[neighbours[i].y][neighbours[i].x] < min_neigh) {
				min_neigh = astar[neighbours[i].y][neighbours[i].x];
				min_n = coords(neighbours[i].x, neighbours[i].y);
			}
		}
		if (now.x > min_n.x) {
			res.push_back(way('a', abs(now.x - min_n.x)));
			now.x -= abs(now.x - min_n.x);
		}
		if (now.x < min_n.x) {
			res.push_back(way('d', abs(now.x - min_n.x)));
			now.x += abs(now.x - min_n.x);
		}
		if (now.y > min_n.y) {
			res.push_back(way('w', abs(now.y - min_n.y)));
			now.y -= abs(now.y - min_n.y);
		}
		if (now.y < min_n.y) {
			res.push_back(way('s', abs(now.y - min_n.y)));
			now.y += abs(now.y - min_n.y);
		}
	}
	return res;
}
