#include <cstdlib>
#include "block.h"
#include <ctime>
#include "shape.h"


// the function init block- input - board_start- the location where the board start 
// the block saved relativetly to the starting pos of the board
void Block::init_block(int board_start)
{
	_boardStartPos = board_start;
	shape.init_shape();
	points->init_points(0, 0);
	change_block_rotation(true); // change the points to curr rotation pos

}

//the function checks the difference between curr block position to board start postion
// diff_x and diff_y update accordenly
// bool new block is a flag - case true: defualt start pos (0,5). case false: need to calaculate 
// according curr block postion (befor change)
void Block::check_points_diff(int& diff_x, int& diff_y, const bool new_block, Point const& p2) const
{
	if (new_block)
	{
		diff_x = starting_x - p2.getX();
		diff_y = starting_y;
	}
	else
	{
		diff_x = points[0].getX() - p2.getX();
		diff_y = points[0].getY() - p2.getY();
	}
}

// input : new_block - flag for check_points_diff function
bool Block::change_block_rotation(const bool new_block, const int old_rotation_pos)
{
	int rotation_pos = shape.get_rotation_pos();
	int diff_x = 0, diff_y = 0;
	Point copy[4];
	// copies the "center" of the old roatition to calculae diffence before change
	switch (shape.get_shape_type())
	{
	case Shape::shape_type::Square:
		check_points_diff(diff_x, diff_y, new_block, Shape::SQUARE[old_rotation_pos][0]);
		break;
	case Shape::shape_type::Bomb:
		check_points_diff(diff_x, diff_y, new_block, Shape::BOMB[old_rotation_pos][0]);
		break;
	case Shape::shape_type::T:
		check_points_diff(diff_x, diff_y, new_block, Shape::T_S[old_rotation_pos][0]);
		break;
	case Shape::shape_type::Right_Z:
		check_points_diff(diff_x, diff_y, new_block, Shape::RIGHT_Z[old_rotation_pos][0]);
		break;
	case Shape::shape_type::Left_Z:
		check_points_diff(diff_x, diff_y, new_block, Shape::LEFT_Z[old_rotation_pos][0]);
		break;
	case Shape::shape_type::Row:
		check_points_diff(diff_x, diff_y, new_block, Shape::ROW[old_rotation_pos][0]);
		break;
	case Shape::shape_type::L:
		check_points_diff(diff_x, diff_y, new_block, Shape::L_S[old_rotation_pos][0]);
		break;
	case Shape::shape_type::J:
		check_points_diff(diff_x, diff_y, new_block, Shape::J_S[old_rotation_pos][0]);
		break;

	}


	// copies the new rotation pos in to copy
	for (int i = 0; i < Shape::shape_size; i++)
	{
		copy[i] = points[i];
		switch (shape.get_shape_type())
		{
		case Shape::shape_type::Square:
			copy[i] = Shape::SQUARE[rotation_pos][i];
			break;
		case Shape::shape_type::Bomb:
			copy[i] = Shape::BOMB[rotation_pos][i];
			break;
		case Shape::shape_type::T:
			copy[i] = Shape::T_S[rotation_pos][i];
			break;
		case Shape::shape_type::Right_Z:
			copy[i] = Shape::RIGHT_Z[rotation_pos][i];
			break;
		case Shape::shape_type::Left_Z:
			copy[i] = Shape::LEFT_Z[rotation_pos][i];
			break;
		case Shape::shape_type::Row:
			copy[i] = Shape::ROW[rotation_pos][i];
			break;
		case Shape::shape_type::L:
			copy[i] = Shape::L_S[rotation_pos][i];
			break;
		case Shape::shape_type::J:
			copy[i] = Shape::J_S[rotation_pos][i];
			break;

		}
		// if move return false = means couldnt make a move to point we finish fucntion with flase
		if (!copy[i].move(diff_x, diff_y))
			return false;



	}
	// if all points moved copy points from copy to block-> points
	for (int i = 0; i < Shape::shape_size; i++)
		points[i] = copy[i];
	return true;
}

void Block::print_block(bool color, unsigned char ch) const
{
	int color_num;
	if (color == true)
		color_num = 1 + static_cast<int>(shape.get_shape_type());
	else
		if (ch == ' ')
			color_num = 1;//does not metter -while space
		else
			color_num = 15; //white
	for (int i = 0; i < Shape::shape_size; i++)
	{
		points[i].draw(_boardStartPos, color_num, ch);
	}
}

// the function checks which action dended and calls for othe functions accordenly
void Block::action_block(Block::actions action)
{
	int old_rot_pos = shape.get_rotation_pos();
	switch (action)
	{
	case actions::Right:
		move_points(1, 0);
		break;
	case  actions::Left:
		move_points(-1, 0);
		break;
	case  actions::Clock:
		shape.update_rotation_pos(old_rot_pos + 1);
		change_block_rotation(false, old_rot_pos);
		break;
	case actions::Counter_Clock:
		shape.update_rotation_pos(old_rot_pos - 1);
		change_block_rotation(false, old_rot_pos);
		break;
	case actions::Down:
		move_points(0, 1);
		break;


	}

}

void Block::move_points(const int diff_x, const int diff_y)
{
	Point temp_points[4];
	bool possible_move;
	// copies the new rotation pos into temp points
	for (int i = 0; i < Shape::shape_size; i++)
	{
		temp_points[i] = points[i];
		possible_move = temp_points[i].move(diff_x, diff_y);
		if (!possible_move)
			return;
	}
	// if all points moved, copy points from temp points to block-> points
	for (int i = 0; i < Shape::shape_size; i++)
		points[i] = temp_points[i];
}

void Block::delete_block_from_screen() const
{
	this->print_block(false, ' ');
}

Point const* const  Block::get_points() const {
	return  points;
}

Shape::shape_type Block::get_block_type() const
{
	return shape.get_shape_type();
}

int Block::get_number_of_rotation_ver()
{
	return (int)shape.get_number_of_roatation_ver();
}

bool Block:: operator== (const Block& b2)
{

	for (int i = 0; i < Shape::shape_size; i++)
	{
		if (!(points[i].getX() == b2.points[i].getX() && points[i].getY() == b2.points[i].getY()))
			return false;
	}
	return true;
}
