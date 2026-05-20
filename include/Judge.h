#pragma once
#include "Player.h"
#include "Card.h"

struct JudgementResult {
    std::string text;
    bool result;
};


// static methods so it doesnt need instancing Judge object
struct Judge {
    static JudgementResult can_the_player_buy_the_card(const Player& player, const Card& card);
    static JudgementResult can_the_player_take_tokens(const Player& player, const int tokens_to_take[5]);
    static JudgementResult can_the_bank_give_tokens(const int bank[6], const int tokens_to_give[5]);

};