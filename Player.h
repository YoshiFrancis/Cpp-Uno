#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <string.h>
#include <iostream>
#include <vector>

using types = Card::Uno::types;
using colors = Card::Uno::colors;
using UnoCard = Card::Uno::Card;
using cardsVec = std::vector<UnoCard>;


class Player {
public:

    Player(cardsVec cards, int totalCards, std::string username) 
        : m_cards { cards }, m_totalCards { totalCards }, m_username { username } 
        { }
    
    Player(cardsVec cards, std::string username) 
        : Player(cards, cards.size(), username)
        { }

    Player(std::string username) 
        : Player({}, 0, username)
        { }

    Player()
        : Player({}, 0, "Guest")
        { }

    Player& operator= (const Player& player) {
        if (this == &player) 
            return *this;
        m_username = player.getUsername();

        return *this;
    }

    int getCardCount() const { return m_totalCards; }
    std::string getUsername() const { return m_username; }
    int getWins() const { return m_wins; }

    void acceptCards(cardsVec cards, int totalCards) {
        if (m_totalCards != 0) {
            m_cards.insert(m_cards.end(), cards.begin(), cards.end());
            m_totalCards += totalCards;
        } else {
            m_cards = cards;
            m_totalCards = totalCards;
        }
    }

    UnoCard prompt(std::string& prompt) {

        bool valid = false;
        std::string answer {};
        UnoCard card;
        while (!valid) {
            std::cout << prompt << "\n";
            std::getline(std::cin, answer);
            card = Card::Uno::generateCard(answer, valid);
        }
        if (playCard(card)) 
            return card;
        else 
            return this->prompt(prompt);
        
    }

    void drawCard(UnoCard card) {
        m_cards.push_back(card);
        ++m_totalCards;
    }

    void displayCards() const {
        for (auto& card : m_cards) {
            std::cout << Card::Uno::showName(card) << "\n";
        }
    }

    bool playCard(const UnoCard &playCard) {
        for (cardsVec::iterator iter = m_cards.begin(); iter != m_cards.end(); ++iter) {
            if (iter->type == playCard.type) {
                m_cards.erase(iter);
                --m_totalCards;
                std::cout << "Playing card!\n";
                return true;
            }
        }
        std::cout << "You do not have that card available!\n";
        return false;
    }

    void win() {
        ++m_wins;
        std::cout << m_username << " has won the game! " << m_username << " has now won " << m_wins << " games!\n";
    }

private:
    cardsVec m_cards {};
    int m_totalCards { 0 };
    std::string m_username;
    unsigned int m_wins { 0 };
};


#endif