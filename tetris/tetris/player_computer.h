#ifndef _TETRIS_COMPUTER_PLAYER
#define _TETRIS_COMPUTER_PLAYER
#include <iostream>
#include "player.h"
#include "move.h"
using std::cout;

class player_computer : public Player
{
	Move move;
	char _level;
	enum MyEnum
	{
		_Rotation=0,
		_Left,
		_Right,
		_Down,
	};
	static constexpr int NUMBER_OF_OPTIONS = 48;
	bool check_action_and_collision(Block::actions action, Board& b, int * steps, int arrayloc);
	Move best_move();
	Move random_move();
	Move good_or_random_move();
	void steps_to_a_move(); // makes a step acorrding move
public:
	
	player_computer(int player, char level) : Player(player), move() { _level = level; cout << "player " << player << " is a level '"<< _level<< "' computer\n"; }
	virtual void turn(bool& collied, int& _gameStatus);
	virtual void auto_drop_block(bool& board_collided, int& gameStatus) {}



};
#endif

