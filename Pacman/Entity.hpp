/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "Map.hpp"

#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68

class Entity {
    public:

        enum EntityType {
            PLAYER,
            GHOST
        };

        enum Direction {
            NONE = 1,
            UP = UP_ARROW,
            DOWN = DOWN_ARROW,
            RIGHT = RIGHT_ARROW,
            LEFT = LEFT_ARROW
        };

        Entity(EntityType type, Map *map);
        ~Entity();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void move();
        void setDir(Direction dir);
    protected:
        Map *_map;
        int _x;
        int _y;
        Direction _dir;

    private:
        EntityType _type;
        char _carac;
        void _getPos();
};

#endif /* !ENTITY_HPP_ */