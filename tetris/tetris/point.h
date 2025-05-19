#ifndef POINT_H
#define POINT_H


class Point {
	int _x;
	int _y;

public:

	Point(const int x, const int y) { _x = x; _y = y; }
	Point() { _x = 0; _y = 0; }

	void init_points(const int x, const int y) { _x = x; _y = y; }
	void draw(const int board_start_pos, int back_color, unsigned char ch = 219) const;
	bool move(const int  diff_x = 0, const int diff_y = 0);
	int getX() const { return _x; }
	int getY() const { return _y; }
	bool check_point_in_board(const int diff_x, const int diff_y) const;

};


#endif 