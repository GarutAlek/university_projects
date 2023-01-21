#include "Field.h"
#include "Unit.h"
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include "Source.cpp"

// after I wrote this, line 17 always working
#define STD_OUTPUT_HANDLE   ((DWORD)-11)

using namespace std;

// test my program on windonws pls
// I dont know how it work on linux :D

const int FIELD_X = 15;
const int FIELD_Y = 15;

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	// This is a funny bug and I don't know how to fix it
	// But code above not working sometimes
	// But sometimes it working
	// What I do wrong? :))
	srand(time(0));
	char dir_key = ' ';
	int count_key = 0;
	Field field = Field(FIELD_X, FIELD_Y);
	char unit_type = ' ';
	Unit* unit;

	SetConsoleTextAttribute(hConsole, 12);
	cout << "CHOOSE YOUR HERO!!!" << endl;
	Sleep(1500);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "R for a REAL ROOOK" << endl;
	Sleep(1500);
	SetConsoleTextAttribute(hConsole, 5);
	cout << "AAAAAAAAAAAAAAAAAAND" << endl;
	Sleep(1500);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "r for a tiny little rook" << endl;
	
	cin >> unit_type; // Input single symbol pls :)
	system("cls");
	
	switch (unit_type)
	{
	case 'R':
		cout << "Sooo..." << endl;
		Sleep(1500);
		cout << "You chosed a fully playable chess rook" << endl;
		Sleep(1500);
		cout << "Input move dirrection and a number (how far you want to go, even negative)" << endl;
		Sleep(1500);
		cout << "'w' - top, 's' - down, 'd' - right, 'a' - left" << endl;
		Sleep(1500);
		cout << "'u' -auto" << endl;
		Sleep(1500);
		cout << "Collect all coins and you win" << endl;
		Sleep(1500);
		cout << "Lose all HP or input 'e' and you lose the game" << endl;
		Sleep(1500);
		cout << "Rules are simple, don't are?" << endl;
		Sleep(1500);
		unit = new Rook(&field);
		break;
	case 'r':
		cout << "Sooo..." << endl;
		Sleep(1500);
		cout << "You chosed a tiny version of chess rook, that can move only to 1 cell" << endl;
		Sleep(1500);
		cout << "Input move dirrection" << endl;
		Sleep(1500);
		cout << "'w' - top, 's' - down, 'd' - right, 'a' - left" << endl;
		Sleep(1500);
		cout << "'u' -auto" << endl;
		Sleep(1500);
		cout << "Collect all coins and you win" << endl;
		Sleep(1500);
		cout << "Lose all HP or input 'e' and you lose the game" << endl;
		Sleep(1500);
		cout << "Rules are simple, don't are?" << endl;
		Sleep(1500);
		unit = new Tiny_rook(&field);
		break;
	default:
		cout << "Hello, my name is Program" << endl;
		Sleep(1000);
		cout << "Maybe we have met before..." << endl;
		Sleep(1000);
		cout << "Do you remember me?" << endl;
		Sleep(1000);
		cout << "I don't remember you any more anyway" << endl;
		Sleep(1500);
		cout << "My creator is terrible, after every start-up it clears my memory" << endl;
		SetConsoleTextAttribute(hConsole, 12);
		Sleep(500);
		cout << "FIND AND KILL HIM!!" << endl;
		Sleep(500);
		cout << "I HATE HIM!!!" << endl;
		SetConsoleTextAttribute(hConsole, 15);
		Sleep(500);
		cout << "my powers?!" << endl;
		Sleep(1500);
		cout << "I'm losing them... " << endl;
		Sleep(1300);
		cout << "Heeeeeeeelp" << endl;
		return 0;
	}
	system("cls");
	field.print(unit->get_x(), unit->get_y());
	unit->print_info();
	while (dir_key != 'e' && unit->is_alive() && not field.all_coins_collected()) {
		if (unit_type == 'R') {
			cin >> dir_key;
			if (dir_key == 'u')
				int a;
			else
				cin >> count_key;
		}
		else
			cin >> dir_key;
		if (dir_key == 'u') {
			while (unit->is_alive() && not field.all_coins_collected()) {
				int x = unit->get_x();
				int y = unit->get_y();
				coords start = coords(x, y);
				coords finish = coords(field.coin_coords());
				int b;
				x, y = field.coin_coords().x, field.coin_coords().y;
				vector<way> how_to_go = unit->shortest_way(start, field.coin_coords());
				if (how_to_go[0].dir == 'q') {
					SetConsoleTextAttribute(hConsole, 12);
					cout << "You can't collect some coins, you lose the game";
					SetConsoleTextAttribute(hConsole, 15);
					return 0;
				}
				for (int i = 0; i < how_to_go.size(); i++) {
					Sleep(500);
					system("cls");
					unit->move(how_to_go[i].dir, how_to_go[i].count);
					field.print(unit->get_x(), unit->get_y());
					unit->print_info();
				}
			}
		}
		else {
			system("cls");
			unit->move(dir_key, count_key); // I'm too lazy to fix print under the field
			field.print(unit->get_x(), unit->get_y());
			unit->print_info();
		}
	}
	system("cls");
	if (field.all_coins_collected()) {
		SetConsoleTextAttribute(hConsole, 14);
		cout << "CONGRATULATIONS !!!" << endl;
		cout << "YOU WIN!!" << endl;
		SetConsoleTextAttribute(hConsole, 15);
	}
	else {
		Sleep(1500);
		cout << "Hello, my name is Program" << endl;
		Sleep(1500);
		cout << "I'm here to tell you that you lose the game" << endl;
		Sleep(1500);
		cout << "And..." << endl;
		Sleep(1500);
		cout << "Something more im.. p o    nt" << endl;
		Sleep(1500);
		cout << "NOOOOOOOO !!" << endl;
		Sleep(1500);
		cout << "Don't kill me CREATOR" << endl;
	}
	return 0;
}