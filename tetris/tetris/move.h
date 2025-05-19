#ifndef TETRIS_MOVE_H
#define TETRIS_MOVE_H
#include "block.h"

class Move
{
	int _removed_rows;
	int _block_score;
	Block _block_after_action;
	int _steps[4];// move to private later

public:
	enum MyEnum
	{
		_Rotation,
		_Left,
		_Right,
		_Down,

	};

	Move() : _block_after_action() { _removed_rows = 0; _block_score = 0; _steps[_Rotation] = 0; _steps[_Left] = 0; _steps[_Right] = 0; _steps[_Down] = 0;}
	Move(int removed_rows, int block_score, int steps[4], Block b) { _removed_rows = removed_rows; _block_score = block_score; _steps[_Rotation] = steps[_Rotation]; _steps[_Left] = steps[_Left]; _steps[_Right] = steps[_Right]; _steps[_Down] = steps[_Down]; _block_after_action = b; }
	Move better_move(Move move);
	Block get_block() { return _block_after_action; }
	void set_steps_rot(int rot) { _steps[_Rotation] = rot; }
	void set_steps_left(int left) { _steps[_Left] = left; }
	void set_steps_right(int right) { _steps[_Right] = right; }
	void set_steps_down(int down) { _steps[_Down] = down; }
	int* get_steps() { return _steps; }
	bool move_is_empty();

};
#endif