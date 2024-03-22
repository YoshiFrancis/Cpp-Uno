#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>
#include <iostream>

namespace Card {
    namespace Uno {
        using types = std::vector<std::string>;
        using colors = std::vector<std::string>;
        extern const types types_char = {"Skip", "Plus 2", "Plus 4", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        extern const colors colors_char = {"Red", "Green", "Blue", "Yellow"};

        enum CardColor {
            RED,
            GREEN,
            BLUE,
            YELLOW,
            maxColors,
        };

        enum CardType {
            SKIP,
            PLUS_TWO,
            PLUS_FOUR,
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            maxTypes,
        };

        struct Card {
            CardType type;
            CardColor color;
        };

        std::string showName(const Card& card) {
            std::string name {};
            name += colors_char[card.color] + ", " + types_char[card.type];
            return name;
        }
    }
};


#endif