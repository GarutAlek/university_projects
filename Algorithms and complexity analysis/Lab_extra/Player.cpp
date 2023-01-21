#include "Player.h"

void Player::move(char way) {
	int dy = 0;
	int dx = 0;
	switch (way)
	{
	case 'w':
		dy--;
		break;
	case 's':
		dy++;
		break;
	case 'a':
		dx--;
		break;
	case 'd':
		dx++;
		break;
	default:
		break;
	}
	if (not field->on_field(coords(pos.x + dx, pos.y + dy)))
		;
	else
		switch (field->get_element(coords(pos.x + dx, pos.y + dy)))
		{
		case 'T':
			if (field->chop_tree(coords(pos.x + dx, pos.y + dy))) {
				pos.x += dx;
				pos.y += dy;
			}
			break;
		case '_':
			pos.x += dx;
			pos.y += dy;
			break;
		default:
			break;
		}
}