#include <iostream>
#include "Card.h"
#include "Player.h"
#include "UnoGame.h"

extern types types_char;
extern colors colors_char;

int main() {

    // UnoCard myCard {Card::Uno::SKIP, Card::Uno::GREEN};
    // cardsVec myCards {{Card::Uno::PLUS_FOUR, Card::Uno::RED}, myCard, myCard};
    // Player francis {myCards, "Yoshi"};
    // francis.displayCards();
    // UnoCard one = Card::Uno::generateCard();
    
    // std::cout << Card::Uno::showName(one) << "\n";
    UnoGame game {};
    game.addPlayers();
    game.displayPlayers();
    game.readInstructioins();
    return 1;
}