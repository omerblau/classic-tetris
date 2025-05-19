#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include "point.h"	
#include "shape.h"


class Block {

public:
	Block() : shape(), points() { _boardStartPos = 0; }
	enum  class actions {
		Right,
		Left,
		Clock,
		Counter_Clock,
		Down
	};

	Point const* const get_points() const;
	void init_block(const int boardStartPos);
	void print_block(bool color, unsigned char ch = 219) const;
	void delete_block_from_screen()const;
	void action_block(Block::actions action); //moves the block according to input
	Shape::shape_type get_block_type() const; // this function return the shape of the block 
	int get_number_of_rotation_ver();
	bool operator== (const Block& b2);

private:
	Point points[4];
	Shape shape;
	int _boardStartPos;

	//block start position x and y values relative to board starting point  
	static const int starting_x = 5;
	static const int starting_y = 0;

	bool change_block_rotation(const bool new_block, const int old_rotation_pos = 0);
	void move_points(const int diff_x, const int diff_y); // moves all block points
	void check_points_diff(int& diff_x, int& diff_y, const bool new_block, Point const& p2) const; // calculates the diffrence between two points

};
#endif
