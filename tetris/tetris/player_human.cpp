#include "player_human.h"
#include "player.h"
#include "block.h"
#include "board.h"



void player_human::turn(bool& collied, int& _gameStatus)
{
	Block temp = board.getBlock();
	temp.delete_block_from_screen();

	board.action_if_possible(convert_input(_key_pressed));
	board.printCurrBlock();
	collied = board.check_block_collision(_gameStatus);
	if (collied)
		board.remove_full_rows();

}


// converts char to enum
Block::actions player_human::convert_input(char ch) const
{
	if (board.getPlayer() == 1)
	{
		switch (ch)
		{
		case 'a':
		case 'A':
			return Block::actions::Left;
		case 'd':
		case 'D':
			return Block::actions::Right;
		case 's':
		case 'S':
			return Block::actions::Clock;
		case 'w':
		case 'W':
			return Block::actions::Counter_Clock;
		case 'x':
		case 'X':
			return Block::actions::Down;
		default:
			break;
		}
	}
	else
	{
		switch (ch)
		{
		case 'j':
		case 'J':
			return Block::actions::Left;
		case 'l':
		case 'L':
			return Block::actions::Right;
		case 'k':
		case 'K':
			return Block::actions::Clock;
		case 'i':
		case 'I':
			return Block::actions::Counter_Clock;
		case 'm':
		case 'M':
			return Block::actions::Down;
		default:
			break;
		}
	}
}