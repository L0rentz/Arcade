/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** SFMLlib
*/

#include "SFMLlib.hpp"

SFMLlib::SFMLlib()
{
}


SFMLlib::~SFMLlib()
{
    _window.close();
}

bool SFMLlib::init(const std::string &map, std::map<char, std::string> tileMap)
{
    (void)map;

    _window.create(sf::VideoMode(1920, 1080), "SFML");

    for (auto itr : tileMap) {
        _listText.push_back(new sf::Texture);
        _listText.back()->loadFromFile(itr.second);
        _tileMap.insert(std::make_pair(itr.first, new sf::Sprite));
        _tileMap[itr.first]->setTexture(*_listText.back());
    }

    _font.loadFromFile("db/fonts/Cornerstone.ttf");
    _text.setFont(_font);

    return (true);
}

void SFMLlib::display()
{
    _window.display();
}

void SFMLlib::draw(std::vector<std::string> map)
{
    char c;

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            c = map[i][j];
            if (_tileMap[c]) {
                _tileMap[c]->setPosition(sf::Vector2f(j * 32, i * 32));
                _window.draw(*_tileMap[c]);
            }
        }
    }
}

Key SFMLlib::getKeyPressed()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return (K_EXIT);
        if (_event.type == sf::Event::TextEntered) {
            if (_event.text.unicode < 128)
                return ((Key)_event.text.unicode);
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::Up)
                return (K_UP);
            if (_event.key.code == sf::Keyboard::Down)
                return (K_DOWN);
            if (_event.key.code == sf::Keyboard::Left)
                return (K_LEFT);
            if (_event.key.code == sf::Keyboard::Right)
                return (K_RIGHT);
            if (_event.key.code == sf::Keyboard::Num1)
                return (K_PREV_LIB);
            if (_event.key.code == sf::Keyboard::Num2)
                return (K_NEXT_LIB);
            if (_event.key.code == sf::Keyboard::Num3)
                return (K_PREV_GAME);
            if (_event.key.code == sf::Keyboard::Num4)
                return (K_NEXT_GAME);
            if (_event.key.code == sf::Keyboard::Space)
                return (K_SPACE);
            if (_event.key.code == sf::Keyboard::Backspace)
                return (K_DEL);
        }
    }
    return (NONE);
}

void SFMLlib::drawText(size_t x, size_t y, std::string text, size_t size)
{
    _text.setString(text);
    _text.setCharacterSize(size);
    _text.setPosition(sf::Vector2f{(float)x, (float)y});
    _window.draw(_text);
}

void SFMLlib::clear()
{
    _window.clear();
}

extern "C" IGfx *createGFX()
{
    return (new SFMLlib);
}

extern "C" void destroyGFX(IGfx *lib)
{
    delete lib;
}