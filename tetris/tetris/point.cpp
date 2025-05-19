#include "point.h"
#include "general.h"
#include "board.h"
#include <iostream>
#include <Windows.h>


void  Point::draw(const int board_start_pos, int back_color, unsigned char ch) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, back_color);
	gotoxy(_x + board_start_pos + 1, _y + 1);
	std::cout << ch;
}
bool  Point::move(const int diff_x, const int diff_y)
{
	if (check_point_in_board(diff_x, diff_y))
	{
		this->_x += diff_x;
		this->_y += diff_y;
		return true;
	}
	return false;
}
bool Point::check_point_in_board(const int diff_x, const int diff_y) const
{
	if (_x + diff_x > Board::BOARD_WIDTH - 1 || _x + diff_x < 0 || _y + diff_y >= Board::BOARD_LENGTH || _y + diff_y < 0)
		return false;
	return true;
}
