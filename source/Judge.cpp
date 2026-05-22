#include <Judge.h>

JudgementResult Judge::can_the_player_buy_the_card(const Player& player, const Card& card) {
	std::string color_names[] = { "white", "red", "green", "blue", "black" };
	std::string missing_colors = "";
	int gold_needed = 0;

	for (int i = 0; i < 5; i++) {
		int shortage = card.cost[i] - player.tokens[i] - player.card_counts[i];
		if (shortage > 0) {
			gold_needed += shortage;
			if (gold_needed > player.tokens[5]) {
				missing_colors += color_names[i] + ", ";
			}
		}
	}

	if (missing_colors.empty()) {
		return JudgementResult("The card can be bought by the player.", true);
	}

	missing_colors.erase(missing_colors.size() - 2);
	return JudgementResult("Not enough tokens (" + missing_colors + ")", false);

};

JudgementResult Judge::can_the_player_take_tokens(const Player& player, const int tokens_to_take[5]) {

	int total_tokens_to_take = tokens_to_take[0] + tokens_to_take[1] + tokens_to_take[2] + tokens_to_take[3] + tokens_to_take[4];
	int players_curr_tokens = player.tokens[0] + player.tokens[1] + player.tokens[2] + player.tokens[3] + player.tokens[4];
	if (players_curr_tokens + total_tokens_to_take > 10) {
		return JudgementResult(
			"The player will have more than 10 tokens!"
			, false);
	}
	if (total_tokens_to_take > 3) {
		return JudgementResult(
			"The player can not take more than 3 tokens!"
			, false);
	}
	if (total_tokens_to_take == 0) {
		return JudgementResult(
			"The player can not take no tokens!",
			false);
	}
	bool same_tokens = false;
	if (total_tokens_to_take == 3) {
		for (int i = 0; i < 5; i++) {
			if (tokens_to_take[i] > 1) {
				return JudgementResult(
					"The player can not take 2 tokens from one color while taking 3 tokens in total."
					, false);
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (tokens_to_take[i] == 2)
			same_tokens = true;
	}
	if (total_tokens_to_take + players_curr_tokens < 10 && total_tokens_to_take < 3 && !same_tokens)
		return JudgementResult(
			"The player should take more tokens."
			, false);


	return JudgementResult(
		"The player can take the tokens."
		, true);
};


JudgementResult Judge::can_the_bank_give_tokens(const int bank[6], const int tokens_to_give[5]) {
	for (int i = 0; i < 5; i++) {
		if (tokens_to_give[i] > bank[i]) {
			return JudgementResult(
				"Not enough tokens in the bank."
				, false);

		}
		if (tokens_to_give[i] > 2) {
			return JudgementResult("Cannot take more than 2 same tokens.",
				false);
		}
		if (tokens_to_give[i] == 2 && bank[i] < 4) {
			return JudgementResult("Cannot take 2 tokens of the same type because there are less than 4 tokens of that type in the game." ,
				false);
		}
	}
	return JudgementResult("The bank can give the tokens.",
		true);
};
