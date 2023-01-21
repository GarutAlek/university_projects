#include "Field.h"
#include "Player.h"

int main() {
	int field_x = 200;
	int field_y = 200;

	int start_x = field_x / 2;
	int start_y = field_y / 2;
	float vision_range = 10.7;

	Field f = Field(field_x, field_y, coords(start_x, start_y));
	Player p = Player(start_x, start_y, vision_range, &f);

	cout << "'e' - for exit program" << endl;

	f.print(p.get_pos(), p.get_vis());

	
	char input = '-';
	while (input != 'e') {
		char input = _getch();
		//cout << endl;
		p.move(input);
		system("cls");
		f.print(p.get_pos(), p.get_vis());
	}
}