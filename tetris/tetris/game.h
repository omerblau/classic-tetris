#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "board.h"
#include "player.h"


class Board;

class Game
{
private:
	Player *player1;
	Player *player2;
	bool _savedGame;
	bool color = false;

	static constexpr int HUMAN_VS_HUMAN  = 1;
	static constexpr int HUMAN_VS_COMPUTER = 2;
	static constexpr int COMPUTER_VS_COMPUTER = 3;
	char menu() const;
	void new_game(int mode);
	void game_round();
	void continue_game();
	void print_game_rules()  const;
	void show_consol_cursor(bool showFlag = false);
	void game_winner();
	void make_player(int player, char player_type);


	int _gameStatus;


public:

	Game() : player1(nullptr), player2(nullptr) { _savedGame = false; _gameStatus = 0; }
	void run();

};
#endif

