#ifndef TETRIS_PLAYER_H
#define TETRIS_PLAYER_H
#include "board.h"



class Player
{

	int _player_num;
protected:

	Board board;
	char _key_pressed;
	Player(int player) : board(player) {  _player_num = player; _key_pressed = ' '; }


public:
	
	void init_board_arr() { board.init_board_arr(); }

	void print_saved_board() { board.print_saved_board(); }

	void draw_boarder_and_score() { board.draw_boarder_and_score(); }

	void remember_key(char p) { _key_pressed = p; }

	int get_score() const { return board.get_score(); }



	virtual void auto_drop_block(bool& board_collided, int& gameStatus) {}

	virtual void turn(bool& collied, int& _gameStatus) {}

};
#endif

