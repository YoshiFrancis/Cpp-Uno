#ifndef UNOGAME_H
#define UNOGAME_H
#include "Card.h"
#include "Player.h"
#include <iostream>

/*
1. start game
2. ask for number of users and get them to enter in usernames
3. add users to vector array
4. read out instruction text to terminal 
5. begin game by giving all players 5 cards (no set sized deck -- all cards will be random)
6. loop through vector of players and tell them to play card or draw
7. run game until one player has one card
8. ask if players would like to play again
*/



class UnoGame {
public:

    UnoGame(std::vector<Player> players) : m_players { players }
        { }
    UnoGame()=default;
    
    void addPlayers(std::initializer_list<Player> players) {
        for (auto& player : players) {
            m_players.push_back(player);
        }
    }

    void addPlayers() {
        bool more = true;
        while (more) {
            Player new_player = addPlayer(more);
            if (more) 
                m_players.push_back(new_player);
        }
        
    }

    void displayPlayers() {
        for (auto& player : m_players) {
            std::cout << player.getUsername() << "\n";
        }
    }

    UnoCard drawCard() {
        return Card::Uno::generateCard();
    } 

private:
    // would like to use move semantics in the future for better optimazation
    // I have uneccessary creating of Player classes several times unneedlessly
    Player addPlayer(bool& more) {
        char answer {};
        while (answer != 'n' && answer != 'y') {
            std::cout << "Would a player like to join (y/n): ";
            std::cin >> answer;
            if (answer == 'n') {
                more = false;
                return {};
            } else if (answer == 'y') {
                std::string username {};
                while (username.size() <= 3 || username.size() >= 15) {
                    std::cout << "Give a username in the length range of [3, 15]: ";
                    std::getline(std::cin, username);
                }
                more = true;
                return { username };    
            } else {
                std::cout << "Enter in y or n\n";
            }
        }

        return {};

    }
    std::vector<Player> m_players;
    UnoCard m_prevCard {};
    unsigned int m_currPlayer { 0 };
    int m_moves { 0 };
    

};


#endif