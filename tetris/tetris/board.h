#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H
#include "block.h"

class Move;
class Board
{
public:

	static constexpr int BOARD_WIDTH = 12;
	static constexpr int BOARD_LENGTH = 18;

	static constexpr int START_POS_PLAYER1 = 0;
	static constexpr int START_POS_PLAYER2 = 25;

	static constexpr int GAME_OVER = 0;
	static constexpr int GAME_PAUSED = 1;
	static constexpr int GAME_CONTINUES = 2;

	Board(int player);
	void draw_boarder_and_score() const;
	bool check_block_collision(int& gameStatus, bool called_from_best_move = false);
	void init_board_arr();
	void game_over(int& gameStatus);
	void auto_drop_block(bool& board_collided, int& gameStatus);
	void print_saved_board(unsigned char ch = 219) const;
	void delete_only_board_content() const;
	void remove_full_rows();
	int get_score() const;
	static bool is_color_on() { return _color; }
	static void set_color_mode(bool color_on) { _color = color_on; }
	Move calc_move(Board const &  temp, int steps[3]) const; // the function calculate move's paramters and returns the move
	int get_block_max_row() const; //return the highes row the block "sits" in
	int getColor()  const { return _color; }
	Block getBlock() const { return block; }
	bool action_if_possible(Block::actions action);
	int getPlayer()  const { return _player; }
	void printCurrBlock() const { block.print_block(_color); }
	void update_block(Block b) { block = b; } 

private:

	static bool _color;
	int _player;
	int _score;
	int _boardStartPos;
	Block block;

	int numOfPointsInRow[BOARD_LENGTH];
	int boardArray[BOARD_LENGTH + 1][BOARD_WIDTH]; // plus one for bottom row of ones

	void init_board_starting_pos(int player);
	void delete_data_after_bomb(); // deletes from array the relevant points after a bomb collied in board
	void drop_hang_squars(int x, int y); // drop down "hang" in the air points after bomb
	void updatenumOfPointsInRow(); // uoadtes the counter array of the number of points of blocks in baord
	int number_of_empty_row_in_board() const; //return the number of rows without blocks in them


};


#endif