#include "move.h"


Move Move::better_move(Move move)
{
	if (this->_removed_rows < move._removed_rows)
		return move;
	else if (this->_removed_rows > move._removed_rows)
		return *this;
	else 
	{
		if (this->_block_score < move._block_score) //smaller mean taller
			return move;
		else if (this->_block_score > move._block_score)
			return *this;
		else
		{
			if (this->_steps[_Right] + this->_steps[_Left] < move._steps[_Right] + move._steps[_Left]) //means that the computer will rather pick blocks that are closer to the walls
				return move;
			else
				return *this;
		}
	}
	return *this;
}


bool Move::move_is_empty()
{
	if (_steps[0] + _steps[1] + _steps[2] + _steps[3] == 0)
		return true;
	return false;
}