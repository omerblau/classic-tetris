#ifndef _SHAPE_H
#define _SHAPE_H
#include"point.h"

class Shape
{

public:
	enum class shape_type {
		Square = 1,
		T,
		Right_Z,
		Left_Z,
		Row,
		L,
		J,
		Bomb
	};
	enum class shape_rotation_versions {
		Square_r = 1,
		Bomb_r = 1,
		T_r = 4,
		Right_Z_r = 2,
		Left_Z_r = 2,
		Row_r = 2,
		L_r = 4,
		J_r = 4
	};
	int static constexpr shape_size = 4;
	void init_shape();
	void update_rotation_pos(int pos);
	shape_type get_shape_type() const { return this->type; };
	int get_rotation_pos() const { return _rotationPos; }
	shape_rotation_versions get_number_of_roatation_ver();
	static const Point SQUARE[shape_size][shape_size];
	static const Point BOMB[shape_size][shape_size];
	static const Point T_S[shape_size][shape_size];
	static const Point RIGHT_Z[shape_size][shape_size];
	static const Point LEFT_Z[shape_size][shape_size];
	static const Point ROW[shape_size][shape_size];
	static const Point L_S[shape_size][shape_size];
	static const Point J_S[shape_size][shape_size];



private:
	shape_type type;
	int _rotationPos;
	void init_shape_type();
	
	int static constexpr num_of_shape_types = 7;
};

#endif // _SHAPE_H