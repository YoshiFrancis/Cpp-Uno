#ifndef UNOGAME_H
#define UNOGAME_H
#include "Card.h"
#include "Player.h"

class UnoGame {
public:

    UnoGame(std::vector<Player> players) : m_players { players }
        { }
    
    void addPlayers(std::initializer_list<Player> players) {
        for (auto& player : players) {
            m_players.push_back(player);
        }
    }

    UnoCard drawCard() {
        
    } 

private:
    std::vector<Player> m_players;
    UnoCard m_prevCard {};
    int m_moves {};
    

};


#endif