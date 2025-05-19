#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "board.h"
#include "general.h"
#include "shape.h"
#include "point.h"
#include "move.h"


using std::cout;
using std::endl;

// basic constractor, initiates a board for a given player
Board::Board(int player) : block()
{
	init_board_starting_pos(player);
	block.init_block(_boardStartPos);
	init_board_arr();
}

// we check if a block cannot move any more and if it is we check the game status (might be game over)
bool Board::check_block_collision(int& gameStatus, bool called_from_best_move)
{
	bool flag_hit = false;
	Point const* const points = block.get_points();

	for (int pointIndex = 0; pointIndex < Shape::shape_size; pointIndex++)
	{
		if (boardArray[(points + pointIndex)->getY() + 1][(points + pointIndex)->getX()] != 0) // we check agains our block array if any contact point is taken (y+1) if it is we return collided
		{
			flag_hit = true;
			break;
		}
	}

	if (flag_hit) // if we hit, we update our board array
	{
		for (int i = 0; i < Shape::shape_size; i++)
		{
			boardArray[(points + i)->getY()][(points + i)->getX()] = (int)block.get_block_type();
			numOfPointsInRow[(points + i)->getY()]++;
		}
		if (block.get_block_type() == Shape::shape_type::Bomb)
		{
			delete_data_after_bomb();
			if (!called_from_best_move) //in case the function is called from best move we just cheking the move not actualy doing the move
			{
				delete_only_board_content();
				print_saved_board();
			}

		}
		if (!called_from_best_move)
			block.init_block(_boardStartPos); // we reset the "falling block"
	}
	game_over(gameStatus); // we check if game is over
	return flag_hit;
}


//used in the board constractor
void Board::init_board_starting_pos(int player)
{
	if (player == 1)
	{
		_player = 1;
		_boardStartPos = START_POS_PLAYER1;
	}
	else
	{
		_player = 2;
		_boardStartPos = START_POS_PLAYER2;
	}
}

// checks if a wanted action is possible and if it is takes it
bool Board::action_if_possible(Block::actions action)
{
	Block temp = block;
	int i;
	temp.action_block(action);
	Point const* const temp_points = temp.get_points();
	for (i = 0; i < Shape::shape_size; i++)
		if (boardArray[(temp_points + i)->getY()][(temp_points + i)->getX()] != 0)
			break;
	if (block == temp)
		return false;
	if (i == Shape::shape_size)
	{
		block = temp;
		return true;
	}

	return false;

}

// prints the boarder and the score of each board
void Board::draw_boarder_and_score() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	for (int col = _boardStartPos; col <= BOARD_WIDTH + 1 + _boardStartPos; col++)
	{
		gotoxy(col, 0);
		cout << "-";
		gotoxy(col, BOARD_LENGTH + 1);
		cout << "-";
	}

	for (int row = 0; row <= BOARD_LENGTH + 1; row++)
	{
		gotoxy(_boardStartPos, row);
		cout << "|";
		gotoxy(_boardStartPos + BOARD_WIDTH + 1, row);
		cout << "|";
	}
	cout << endl;
	gotoxy(_boardStartPos + 15, 1);
	cout << _score;

}

// initiates the date of the board
void Board::init_board_arr()
{
	_score = 0;
	for (int row = 0; row < BOARD_LENGTH; row++)
	{
		for (int col = 0; col < BOARD_WIDTH; col++)
			boardArray[row][col] = 0;
		numOfPointsInRow[row] = 0;
	}
	for (int col = 0; col < BOARD_WIDTH; col++)
		boardArray[BOARD_LENGTH][col] = 1;
	block.init_block(_boardStartPos);
}

// prints the data of a board
void Board::print_saved_board(unsigned char ch) const
{
	Point p;
	int color_num;
	for (int row = 0; row < BOARD_LENGTH; row++)
	{
		for (int col = 0; col < BOARD_WIDTH; col++)
		{
			if (boardArray[row][col] != 0)
			{
				p.init_points(col, row);
				if (_color == true) //checks
					color_num = 1 + boardArray[row][col];
				else
					if (ch == ' ')
						color_num = 1; //does not metter -while space
					else
						color_num = 15; //white

				p.draw(_boardStartPos, color_num, ch);

			}
		}
	}
	gotoxy(_boardStartPos + 15, 1);
	cout << _score;
}

// uses the board print function with ' ' to clear it without clrscr
void Board::delete_only_board_content() const
{
	Point p;
	for (int row = 0; row < BOARD_LENGTH; row++)
	{
		for (int col = 0; col < BOARD_WIDTH; col++)
		{
			p.init_points(col, row);
			p.draw(_boardStartPos, 0, ' ');
		}

	}
}

// checks if game is over
void Board::game_over(int& gameStatus)
{
	if (numOfPointsInRow[0] != 0)
		gameStatus = GAME_OVER;

}

// uses to clear full rows and score the player
void Board::remove_full_rows()
{
	int RowsCleared = 0;
	delete_only_board_content();

	for (int i = 0; i < BOARD_LENGTH; i++) {
		// If a row is full
		if (numOfPointsInRow[i] == BOARD_WIDTH)
		{
			RowsCleared++;
			// Shift all rows above down by one
			for (int j = i; j > 0; j--)
			{
				for (int k = 0; k < BOARD_WIDTH; k++)
					boardArray[j][k] = boardArray[j - 1][k];
				numOfPointsInRow[j] = numOfPointsInRow[j - 1];
			}
			// Clear the top row
			for (int k = 0; k < BOARD_WIDTH; k++)
				boardArray[0][k] = 0;
			numOfPointsInRow[0] = 0;
		}
	}

	switch (RowsCleared)
	{
	case 1:
		_score += 1000; //bonus 0
		break;
	case 2:
		_score += 2500; //bonus 500
		break;
	case 3:
		_score += 4000; //bonus 1000
		break;
	case 4:
		_score += 6000; //bonus 2000
		break;
	default:
		break;
	}
	print_saved_board();
}


// runs a sequence that drop down the falling block by 1 step
void Board::auto_drop_block(bool& board_collided, int& gameStatus)
{
	block.delete_block_from_screen();
	block.action_block(Block::actions::Down);
	block.print_block(_color);
	board_collided = check_block_collision(gameStatus);
	if (board_collided)
		remove_full_rows();
}


// returns players score
int Board::get_score() const
{
	return _score;
}


void Board::delete_data_after_bomb() // update row counter array need to do it clenaer
{
	Point const* const points = block.get_points();
	int x = points->getX(), y = points->getY();
	Point point;


	for (int i = 0; i < 9; i++)
	{
		if (point.check_point_in_board(x - 4 + i, y))
		{
			if (boardArray[y][(x - 4 + i)] != 0)
				boardArray[y][(x - 4 + i)] = 0;
		}

	}

	for (int i = 0; i < 7; i++) {
		if (point.check_point_in_board(x - 3 + i, y + 1))
			boardArray[y + 1][x - 3 + i] = 0;
		if (point.check_point_in_board(x - 3 + i, y - 1))
			boardArray[y - 1][x - 3 + i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		if (point.check_point_in_board(x - 2 + i, y + 2))
			boardArray[y + 2][x - 2 + i] = 0;
		if (point.check_point_in_board(x - 2 + i, y - 2))
			boardArray[y - 2][x - 2 + i] = 0;
	}

	for (int i = 0; i < 3; i++) {
		if (point.check_point_in_board(x - 1 + i, y + 3))
			boardArray[y + 3][x - 1 + i] = 0;
		if (point.check_point_in_board(x - 1 + i, y - 3))
			boardArray[y - 3][x - 1 + i] = 0;
	}

	if (point.check_point_in_board(x, y + 4))
		boardArray[y + 4][x] = 0;

	if (point.check_point_in_board(x, y - 4))
		boardArray[y - 4][x] = 0;

	drop_hang_squars(x, y);
	updatenumOfPointsInRow();
	//remove_full_rows();



}

bool Board::_color = false;

void Board::drop_hang_squars(int x, int y)
{
	int k;
	int ystop = max(y - 4, 0);
	int ystart = min(y + 4, BOARD_LENGTH - 1);
	int xstop = max(x - 4, 0);
	int xstart = min(x + 4, BOARD_WIDTH - 1);
	int check;
	for (int i = BOARD_LENGTH - 1; i >= 0; i--)
	{
		for (int j = BOARD_WIDTH - 1; j >= 0; j--)
		{
			if (boardArray[i][j] != 0 && boardArray[i + 1][j] == 0)
			{
				k = i + 1;
					while (k < BOARD_LENGTH && boardArray[k][j] == 0  )
					{
						k++;
					}
					boardArray[k - 1][j] = boardArray[i][j];
					boardArray[i][j] = 0;

			}

		}
	}
}


void Board::updatenumOfPointsInRow()
{
	for (int i = BOARD_LENGTH - 1; i >= 0; i--)
	{
		numOfPointsInRow[i] = 0;
		for (int j = BOARD_WIDTH - 1; j >= 0; j--)
		{
			if (boardArray[i][j] != 0)
				numOfPointsInRow[i]++;
		}
	}
}


// return the number of empty rows in board
int Board::number_of_empty_row_in_board() const
{
	int count = 0;
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		if (numOfPointsInRow == 0)
			count++;
	}
	return count;
}




Move Board::calc_move(Board const& temp, int steps[3]) const
{

	int removed_rows = temp.number_of_empty_row_in_board() - number_of_empty_row_in_board();
	int block_score = temp.get_block_max_row();
	Move res(removed_rows, block_score, steps, temp.block);
	return res;
}



int Board::get_block_max_row() const
{
	Point const* points = block.get_points();
	int blockScore = 0; //score is calculated by the sum of Y values for all of the blocks points, higher score means more blocks are lower
	for (int i = 0; i < Shape::shape_size; i++)
	{
		blockScore += (points + i)->getY();
	}
	return blockScore;
}





