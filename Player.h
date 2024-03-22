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

    Player(std::vector<UnoCard> cards, int totalCards, std::string username) 
        : m_cards { cards }, m_totalCards { totalCards }, m_username { username } 
        { }
    
    Player(std::vector<UnoCard> cards, std::string username) 
        : Player(cards, cards.size(), username)
        { }

    Player(std::string username) 
        : Player({}, 0, username)
        { }

    Player()
        : Player({}, 0, "Guest")
        { }

    int getCardCount() const { return m_totalCards; }
    std::string getUsername() const { return m_username; }
    int getWins() const { return m_wins; }

    void acceptCards(std::vector<UnoCard> cards, int totalCards) {
        m_cards = cards;
        m_totalCards = totalCards;
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
        for (std::vector<UnoCard>::iterator iter = m_cards.begin(); iter != m_cards.end(); ++iter) {
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
    std::vector<UnoCard> m_cards {};
    int m_totalCards { 0 };
    const std::string m_username;
    unsigned int m_wins { 0 };
};


#endif