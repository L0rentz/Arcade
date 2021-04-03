/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "Player.hpp"
#include "Ghost.hpp"
#include "IGame.hpp"
#include <chrono>


using my_clock = std::chrono::high_resolution_clock;

class Pacman : public IGame {
    public:
        Pacman();
        ~Pacman();

        void init(const std::string &map);
        std::vector<std::string> getMap() const;
        size_t getScore() const;
        void setKeyPressed(Key k);
        std::map<char, std::string> getTiles() const;
        size_t getBestScore() const;
        std::string getName() const;

    protected:
    private:
        void createGhosts();
        void moveGhosts();
        bool update();
        void getScoreFromFile();
        void setScoreToFile();

        size_t _bestScore;
        std::string _name;
        Key _input;
        Player *_p;
        std::vector<Ghost *> g;
        Map m;
};

#endif /* !PACMAN_HPP_ */
