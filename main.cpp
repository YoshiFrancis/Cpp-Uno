#include <iostream>
#include "Card.h"
#include "Player.h"

extern types types_char;
extern colors colors_char;

int main() {

    UnoCard myCard {Card::Uno::SKIP, Card::Uno::RED};
    cardsVec myCards {{Card::Uno::PLUS_FOUR, Card::Uno::RED}, myCard, myCard};
    Player francis {myCards, "Yoshi"};
    francis.displayCards();
    return 1;
}