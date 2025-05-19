#ifndef _TETRIS_HUMAN_PLAYER
#define _TETRIS_HUMAN_PLAYER
#include <iostream>
#include "player.h"

using std::cout;

class player_human : public Player
{


public:
	player_human(int player) : Player(player) { cout << "player " << player << " is human\n"; }

	virtual void turn(bool& collied, int& _gameStatus);
	virtual void auto_drop_block(bool& board_collided, int& gameStatus) { board.auto_drop_block(board_collided, gameStatus); }

	Block::actions convert_input(char ch) const;


};
#endif
