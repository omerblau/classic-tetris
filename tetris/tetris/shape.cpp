#include "shape.h"
#include <cstdlib>



const Point Shape::SQUARE[4][4] = { Point(0,0),Point(1,0),Point(0,1),Point(1,1) };
const Point Shape::BOMB[4][4]; // is this line does something
const Point Shape::T_S[4][4] = { Point(0,0),Point(1,0),Point(2,0),Point(1,1),Point(1,0), Point(1,1), Point(1,2),Point(0,1), Point(2,1),Point(1,1),Point(0,1),Point(1,0),Point(0,2),Point(0,1),Point(0,0),Point(1,1) };
const Point Shape::RIGHT_Z[4][4] = { Point(2,0),Point(1,0),Point(1,1),Point(0,1),Point(0,0),Point(0,1),Point(1,1),Point(1,2) };
const Point Shape::LEFT_Z[4][4] = { Point(0,0),Point(1,0),Point(1,1),Point(2,1),Point(1,0),Point(1,1),Point(0,1),Point(0,2) };
const Point Shape::ROW[4][4] = { Point(0,0),Point(0,1),Point(0,2),Point(0,3),Point(0,0),Point(1,0),Point(2,0),Point(3,0) };
const Point Shape::L_S[4][4] = { Point(0,0),Point(0,1),Point(0,2),Point(1,2),Point(2,0),Point(1,0),Point(0,0),Point(0,1),Point(1,2),Point(1,1),Point(1,0),Point(0,0),Point(0,1),Point(1,1), Point(2,1) ,Point(2,0) };
const Point Shape::J_S[4][4] = { Point(1,0),Point(1,1),Point(1,2),Point(0,2),Point(2,1),Point(1,1),Point(0,1),Point(0,0) ,Point(0,2),Point(0,1),Point(0,0),Point(1,0),Point(0,0),Point(1,0),Point(2,0),Point(2,1) };
// the function choose shape type and rotation position for each shape
void Shape::init_shape()
{
	init_shape_type();
	switch (this->type)
	{
	case shape_type::Square:
	case shape_type::Bomb:
		this->_rotationPos = (int)shape_rotation_versions::Square_r - 1;
		break;
	case shape_type::T:
	case shape_type::L:
	case shape_type::J:
		this->_rotationPos = rand() % (int)shape_rotation_versions::T_r;
		break;
	case shape_type::Right_Z:
	case shape_type::Left_Z:
	case shape_type::Row:
		this->_rotationPos = rand() % (int)shape_rotation_versions::Row_r;
		break;

	}
}

//this function init shape type that the seven standart in the same probeblity (13.571%) and a bomb in 5% chand
void Shape::init_shape_type()
{
	int number = (rand() % 700); // usead 700 becouse the precentage works in intgers (95= 13.571% and 35 = 5%)
	int delta = 95;
	for (int i = 1; i <= num_of_shape_types; i++)
	{
		if ((number < i * delta) && (number >= (i-1)*delta))
			type = static_cast <shape_type> (i);
	}
	if (number > 664)//664
		type = shape_type::Bomb;

}

// the function update the rotation pos of the shape according to the new pos (input)
void Shape::update_rotation_pos(int pos)
{
	switch (this->type)
	{
	case  shape_type::Square:
	case shape_type::Bomb:
		this->_rotationPos = (int)shape_rotation_versions::Square_r - 1; // square has only one rotation
		break;
	case shape_type::T:
	case shape_type::L:
	case shape_type::J:
		this->_rotationPos = (pos + (int)shape_rotation_versions::T_r) % (int)shape_rotation_versions::T_r;
		break;
	case shape_type::Right_Z:
	case shape_type::Left_Z:
	case shape_type::Row:
		this->_rotationPos = (pos + (int)shape_rotation_versions::Row_r) % (int)shape_rotation_versions::Row_r;
		break;
	}
}

Shape::shape_rotation_versions Shape :: get_number_of_roatation_ver()
{
	switch (type)
	{
	case  shape_type::Square:
	case shape_type::Bomb:
		return shape_rotation_versions::Square_r;
	case shape_type::T:
	case shape_type::L:
	case shape_type::J:
		return shape_rotation_versions::T_r;
	case shape_type::Right_Z:
	case shape_type::Left_Z:
	case shape_type::Row:
		return shape_rotation_versions::Row_r;
	}
}
