#ifndef CARD_H
#define CARD_H
#include "helper.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <random>

namespace Card {
    namespace Uno {
        using types = std::vector<std::string>;
        using colors = std::vector<std::string>;

        std::random_device rd; 
        std::mt19937 gen(rd());
        

        extern const types types_char = {"Skip", "Reverse", "Plus 2", "Plus 4", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        extern const colors colors_char = {"Red", "Green", "Blue", "Yellow", "All"};

        enum CardColor {
            RED,
            GREEN,
            BLUE,
            YELLOW,
            ALL,
            maxColors,
        };

        enum CardType {
            SKIP,
            REVERSE,
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
        
        std::uniform_int_distribution<int> color_distribution(0, maxColors-2);
        std::uniform_int_distribution<int> type_distribution(0, maxTypes-1);

        struct Card {
            CardType type;
            CardColor color;
        };

        std::string showName(const Card& card) {
            std::string name {};
            name += colors_char[card.color] + ", " + types_char[card.type];
            return name;
        }

        Card generateCard() {
            CardColor color = static_cast<CardColor>(color_distribution(gen));
            CardType type = static_cast<CardType>(type_distribution(gen));

            if (type == PLUS_FOUR) 
                color = ALL;
            return { type, color };
        }

        Card generateCard(std::string& cardStr, bool& valid) {
            std::string delimiter = ",";
            auto delimiterPos = cardStr.find(delimiter);
            std::string color = cardStr.substr(0, delimiterPos);
            std::string type = cardStr.substr(delimiterPos + delimiter.size(), cardStr.find('\n'));
            Helper::capitalizeOnly(color);
            Helper::capitalizeOnly(type);
            std::cout << color << "\n" << type << "\n";

            // validation that is card while also getting the specifc volotd
            int color_idx, type_idx;
            for (color_idx = 0; color_idx < maxColors; ++color_idx) {
                if (colors_char[color_idx] == color) 
                    break;
            }
            if (color_idx == maxColors) {
                valid = false;
                return {};
            }
            for (type_idx = 0; type_idx < maxTypes; ++type_idx) {
                if (types_char[type_idx] == type) 
                    break;
            }

            if (type_idx == maxTypes) {
                valid = false;
                return {};
            }
            std::cout << "card is valid?\n";

            valid = true;

            return { static_cast<CardType>(type_idx), static_cast<CardColor>(color_idx) };
        }
    }
};


#endif