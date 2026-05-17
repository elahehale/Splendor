// Config.h
#pragma once

namespace Config {
    inline int WINNING_SCORE = 15;
    inline int MAX_RESERVED_CARDS = 3;
    inline bool DEBUG_MODE = false;
	inline std::string ERROR_BUY = "Cannot buy the card! Not enough tokens or cards!";
	inline std::string ERROR_TAKE_TOKENS_MAX10 = "Cannot take tokens! You cannot have more than 10 tokens!";
	inline std::string ERROR_TAKE_TOKENS_2SAME = "Cannot take tokens! You cannot take 2 tokens of the same color if there are less than 4 tokens of that color!";
	inline std::string ERROR_TAKE_2SAME_1DIFF_TOKEN = "Cannot take tokens! You cannot take 2 tokens of the same color if you are also taking a token of a different color!";
	inline std::string ERROR_TAKE_2SAME_PLAYER_HAS_2SAME = "Cannot take tokens! You cannot take 2 tokens of the same color if you already have 2 tokens of that color!";
	inline std::string ERROR_RESERVE_MAX = "Cannot reserve the card! You cannot have more than 3 golden tokens!";
	inline std::string INSTRUCTION_BUY_OR_RESERVE = "Do you want to buy or reserve this card? (Y/N)";
	inline std::string INSTRUCTION_TURN = "Buy or reserve a card, or take tokens in your turn!";


}