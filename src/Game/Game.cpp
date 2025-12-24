/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** Game.cpp
*/

#include "configs.hpp"
#include "entities.hpp"
#include "Game.hpp"

Game::Game() : _framelimit(FRAME_LIMIT) {
    loadPlugins();

    for (auto& sys : SYSTEMS_NAME)
        createSystem(sys);
    for (auto& conf : CONFIG_PATHS)
        addConfig(conf);
    for (auto& map : MAP_PATHS)
        addMap(map);

    createMap(eField::MAP_BEGIN, 0);
    createEntity(eField::PLAYER, "player",
        {36.f * 50 / 2, 36.f * 50 / 2});

    createComponent("window", eField::SYSTEM);
    sub("closed", [this]() {_running = false;});
    _running = true;

    setPlayerMovement();
    setMobSpawner();
}

void Game::run() {
    while (_running) {
        if (_framelimit.checkDelay())
            runSystems();
    }
}
