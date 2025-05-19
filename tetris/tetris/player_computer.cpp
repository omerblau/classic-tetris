#include "player_computer.h"
#include "move.h"




// used in a game loop, called when ever a player takes a turn
void player_computer::turn(bool& collied, int& _gameStatus)
{
	if (move.move_is_empty()) // if the array of curr move is empty iniate new move calculation
	{
		char next_step;
		Block temp = board.getBlock();
		temp.delete_block_from_screen();
		move = good_or_random_move();
	}

	board.getBlock().delete_block_from_screen();
	steps_to_a_move();
	board.printCurrBlock();

	collied = board.check_block_collision(_gameStatus);
	if (collied)
		board.remove_full_rows();

}


Move player_computer::good_or_random_move()
{
	if (_level == 'b' &&  rand() % 40 == 0)
			return random_move();
	else if(_level == 'c' && rand() % 10 == 0)
			return random_move();
	return best_move();
}

Move player_computer::random_move() // buldis a randomized move
{
	Board temp_for_calc = board;
	Board copy_for_compare = board;

	Move move;
	int rotation;
	int column;
	bool hit = false;
	int game_status = Board::GAME_CONTINUES;
	int steps[4] = { 0,0,0,0 };

	rotation = rand() % 4;
	steps[1] = rotation;

	column = rand() % 12;
	if (column < 6)
		steps[1] = column;
	else
		steps[2] = column;

	while (!hit)
	{
		temp_for_calc.action_if_possible(Block::actions::Down);
		hit = temp_for_calc.check_block_collision(game_status, true);
		steps[3]++;
	}
	move = copy_for_compare.calc_move(temp_for_calc, steps);

	return move;
}

Move player_computer::best_move()
{
	Move best, curr;
	int game_status = Board::GAME_CONTINUES;
	Board copy_for_compare = board;
	Board temp_for_calc = board;
	Board temp_left_align = board;
	int steps[4];
	int leftMovesForAlignment = 0;

	for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
	{
		bool flag = false;
		for (int s = 0; s < Shape::shape_size; s++)
			steps[s] = 0;
		temp_for_calc = board;

		for (int k = 0; k < (i / 12); k++) // for rotation
			check_action_and_collision(Block::actions::Clock, temp_for_calc, steps,0);

		if ((i / 6) % 2 == 0)
		{
			for (int j = 0; j < (i % 6) + 1; j++) //OPTIONS TO MOVE LEFT
				check_action_and_collision(Block::actions::Left, temp_for_calc, steps,1);
		}
		else
		{
			for (int j = 0; j < (i % 6) + 1; j++) //OPTIONS TO MOVE RGI
				check_action_and_collision(Block::actions::Right, temp_for_calc, steps,2);
		}
		while (!flag)
			flag = check_action_and_collision(Block::actions::Down, temp_for_calc, steps,3);
	
		curr = copy_for_compare.calc_move(temp_for_calc, steps);
		best = best.better_move(curr);
	}

	bool flag = false;
	for (int s = 0; s < Shape::shape_size; s++)
		steps[s] = 0;
	while (!flag)
		flag = check_action_and_collision(Block::actions::Down, temp_for_calc, steps,3);
	curr = copy_for_compare.calc_move(temp_for_calc, steps);
	best = best.better_move(curr);
	return best;
}

bool player_computer:: check_action_and_collision(Block::actions action,Board& b,int * steps, int arrayloc)
{
	int game_status = Board::GAME_CONTINUES;
	b.action_if_possible(action);
	bool flag = b.check_block_collision(game_status, true);
	(* (steps + arrayloc))++;
	return flag;
}


void player_computer::steps_to_a_move()
{
	if (*(move.get_steps() + _Rotation) > 0)
	{
		move.set_steps_rot(--(*(move.get_steps() + _Rotation)));
		board.action_if_possible(Block::actions::Clock);
	}
	else if (*(move.get_steps() + _Left) > 0)
	{

		move.set_steps_left(--(*(move.get_steps() + _Left)));
		board.action_if_possible(Block::actions::Left);
	}
	else if (*(move.get_steps() + _Right) > 0)
	{
		move.set_steps_right(--(*(move.get_steps() + _Right)));
		board.action_if_possible(Block::actions::Right);
	}
	else
	{
		move.set_steps_down(--(*(move.get_steps() + _Down)));
		board.action_if_possible(Block::actions::Down);
	}
}