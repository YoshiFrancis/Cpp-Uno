#ifndef UNOGAME_H
#define UNOGAME_H
#include "Card.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


/*
I have implemented the game so that the UnoGame class draws for the players. The players have the functionality to receive the cards.
This is for the purpose of reusing the players with different card games which may use different card types. The players must receive
card types of any type.

TODO
1. start game -- DONE
2. ask for number of users and get them to enter in usernames -- DONE
3. add users to vector array -- DONE
4. read out instruction text to terminal  -- DONE
5. begin game by giving all players 5 cards (no set sized deck -- all cards will be random) -- DONE
6. loop through vector of players and tell them to play card or draw
7. run game until one player has one card
8. ask if players would like to play again
*/



class UnoGame {
public:

    UnoGame(std::vector<Player> players) : m_players { players }
        { }
    UnoGame()=default;
    
    UnoCard getTopCard() {
        return m_prevCard;
    }

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

    void displayTopCard() {
        Card::Uno::showName(m_prevCard);
    }

    void beginGame() {
        addPlayers();
        readInstructionsTxt();
        readBeginGameTxt();
        std::cout << "\n\n\n\n";
        for (auto& player : m_players) 
            givePlayerCards(player, drawCards(baseAmount));
        m_prevCard = drawCard();
        displayTopCard();

        // playing the actual game now with all the rounds and moves by players
        while (true) {
            for (auto& player: m_players) {
                UnoCard playedCard = askPlayer(player);
                m_prevCard = playedCard;
                displayTopCard();
            }
        }
    }

    UnoCard askPlayer(Player& player) {
        std::string prompt;
        std::ostringstream os;
        os << player.getUsername() << ", enter the card you would like to place down <COLOR>,<TYPE>: ";
        prompt = os.str();
        player.displayCards();
        return player.prompt(prompt);
    }

    void givePlayerCards(Player& player, cardsVec cards) {
        player.acceptCards(cards, cards.size());
    }

private:
    // would like to use move semantics in the future for better optimazation
    // I have uneccessary creating of Player classes several times unneedlessly
    Player addPlayer(bool& more) {
        char answer {};
        while (answer != 'n' && answer != 'y') {
            std::cout << "Would a player like to join (y/n): ";
            std::cin >> answer;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    
        void readInstructionsTxt() {
        std::ifstream outf{ "introduction.txt", std::ios::in };
        std::string introTxt {};
        std::cout << "Welcome";
        for (auto player = m_players.begin(); player != m_players.end(); player++) {
            if (player == m_players.end() - 1) 
                std::cout << " and " << player->getUsername() << "!\n";
            else {
                std::cout << " " << player->getUsername() << ",";
            }
        }
        while (std::getline(outf, introTxt)) 
            std::cout << introTxt << "\n";
    }

    void readBeginGameTxt() {
        std::ifstream inf{ "begin.txt", std::ios::in };
        std::string beginTxt {};
        while (std::getline(inf, beginTxt))
            std::cout << beginTxt << "\n";
    }

    cardsVec drawCards(int count) {
        cardsVec new_cards(count);
        for (int idx { 0 }; idx < count; ++idx) {
            new_cards[idx] = drawCard();
        }
        return new_cards;
    }

    UnoCard drawCard() {
        return Card::Uno::generateCard();
    } 

    void displayAllCards() {
        for (auto& player : m_players) {
            std::cout << player.getUsername() << ":\n";
            player.displayCards();
            std::cout << "\n";
        }
    }

    std::vector<Player> m_players;
    UnoCard m_prevCard {};
    unsigned int m_currPlayer { 0 };
    int m_moves { 0 };
    const int baseAmount = 5;
    

};


#endif