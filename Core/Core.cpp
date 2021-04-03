/*
** EPITECH PROJECT, 2021
** B-OOP-400-NCE-4-1-arcade-marton.szuts
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(char *lib)
{
    this->_lib = nullptr;
    this->_game = nullptr;
    this->openGfx(lib);
    this->openGame((char *)"lib/arcade_menu.so");
    this->_game->init("");
    this->_lib->init("", this->_game->getTiles());
    this->parseLibs();
    _scene = MENU;
    this->_libIdx = 0;
    this->_gameIdx = 0;

    for (size_t i = 0; i != _libNames.size(); i++) {
        if (strcmp(_libNames[i].c_str(), lib) == 0)
            break;
        _libIdx++;
    }
    _saveGameIdx = _gameIdx;
}

Core::~Core()
{
}

void Core::parseLibs()
{
    std::ifstream file;
    std::string line;
    file.open("db/libs/config.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.substr(line.find('=') + 1) == "game")
                _gameNames.push_back(line.substr(0, line.find('=')));
            if (line.substr(line.find('=') + 1) == "gfx")
                _libNames.push_back(line.substr(0, line.find('=')));
        }
        file.close();
    }
}

void Core::openGfx(const char *path)
{
    this->_dlGfx.open((char *)path, RTLD_LAZY | RTLD_GLOBAL);
    createGFX *gfx = (createGFX *)this->_dlGfx.sym("createGFX");
    this->_lib = gfx();
}

void Core::openGame(const char *path)
{
    this->_dlGame.open((char *)path, RTLD_LAZY | RTLD_GLOBAL);
    createGame *game = (createGame *)this->_dlGame.sym("createGame");
    this->_game = game();
}

void Core::changeGfxLib(const char *path)
{
    destroyGFX *dGfx = (destroyGFX *)this->_dlGfx.sym("destroyGFX");
    if (_lib != nullptr) dGfx(_lib);
    _lib = nullptr;
    this->_dlGfx.close();
    this->openGfx(path);
    this->_lib->init("", this->_game->getTiles());
}

void Core::changeGameLib(const char *path)
{
    destroyGame *dGame = (destroyGame *)this->_dlGame.sym("destroyGame");
    if (_game != nullptr) dGame(_game);
    _game = nullptr;
    this->_dlGame.close();
    destroyGFX *dGfx = (destroyGFX *)this->_dlGfx.sym("destroyGFX");
    if (_lib != nullptr) dGfx(_lib);
    _lib = nullptr;
    this->_dlGfx.close();
    this->openGfx(_libNames[_libIdx].c_str());
    this->openGame(path);
    this->_game->init("");
    this->_lib->init("", this->_game->getTiles());
}

void Core::handleKeyPressed()
{
    if (this->_k == K_PREV_LIB) {
        _libIdx--;
        if (_libIdx < 0) _libIdx = _libNames.size() - 1;
        this->changeGfxLib(_libNames[_libIdx].c_str());
    }
    else if (this->_k == K_NEXT_LIB) {
        _libIdx++;
        if (_libIdx > (int)_libNames.size() - 1) _libIdx = 0;
        this->changeGfxLib(_libNames[_libIdx].c_str());
    }
    if (this->_scene == GAME) {
        if (this->_k == K_PREV_GAME) {
            _gameIdx--;
            if (_gameIdx < 0) _gameIdx = _gameNames.size() - 1;
            this->changeGameLib(_gameNames[_gameIdx].c_str());
        }
        else if (this->_k == K_NEXT_GAME) {
            _gameIdx++;
            if (_gameIdx > (int)_gameNames.size() - 1) _gameIdx = 0;
            this->changeGameLib(_gameNames[_gameIdx].c_str());
        }
    }
    else if (this->_scene == MENU) {
        if (this->_k == K_LEFT) {
            _gameIdx--;
            if (_gameIdx < 0) _gameIdx = _gameNames.size() - 1;
        }
        else if (this->_k == K_RIGHT) {
            _gameIdx++;
            if (_gameIdx > (int)_gameNames.size() - 1) _gameIdx = 0;
        }
    }
}

void Core::run()
{
    while ((this->_k = this->_lib->getKeyPressed()) != K_EXIT) {
        this->handleKeyPressed();
        this->_game->setKeyPressed(this->_k);
        if (this->_game->update()) {
            if (_scene == GAME) {
                _scene = MENU;
                _gameIdx = _saveGameIdx;
                this->changeGameLib("lib/arcade_menu.so");
            }
            else {
                _scene = GAME;
                this->changeGameLib(_gameNames[_gameIdx].c_str());
            }
        }
        this->_lib->clear();
        this->_lib->draw(this->_game->getMap());
        if (this->_scene == GAME) {
            this->_lib->drawText(910, 45, "name: " + this->_game->getName());
            this->_lib->drawText(910, 10, "score: " + std::to_string(this->_game->getScore()));
        }
        this->_lib->display();
    }
}