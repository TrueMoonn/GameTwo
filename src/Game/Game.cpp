/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** Game.cpp
*/

#include "ECS/Entity.hpp"
#include "Game/components.hpp"
#include "Game/signals.hpp"
#include "Game/systems.hpp"
#include "configs.hpp"
#include "entities.hpp"
#include "Game.hpp"

Game::Game() : _framelimit(FRAME_LIMIT) {
    loadPlugins();

    for (auto& func : SYSTEMS)
        func(*this);
    for (auto& sys : PLUGIN_SYSTEMS)
        createSystem(sys);

    for (auto& func : COMPONENTS)
        func(*this);
    for (auto& func : SIGNALS)
        func(*this);
    for (auto& conf : CONFIG_PATHS)
        addConfig(conf);
    for (auto& map : MAP_PATHS)
        addMap(map);

    _nextEntities[EntityType::SYSTEM] = eField::SYSTEM_F;
    _nextEntities[EntityType::PLAYER] = eField::PLAYER_F;
    _nextEntities[EntityType::MAP] = eField::MAP_BEGIN;
    _nextEntities[EntityType::MOB] = eField::MOB_BEGIN;

    _nextEntities.at(MAP) = createMap(nextEntity(MAP), 0) + 1;
    createEntity(nextEntity(PLAYER), "player",
        {36.f * 50 / 2, 36.f * 50 / 2});

    createComponent("window", nextEntity(SYSTEM));
    sub("closed", [this]() {_running = false;});
    _running = true;
}

ECS::Entity Game::nextEntity(EntityType type) {
    if (_nextEntities.at(type) > ENTITY_FIELDS.at(type).max) {
        _nextEntities.at(type) = ENTITY_FIELDS.at(type).min;
    } else {
        _nextEntities.at(type) += 1;
    }
    return _nextEntities.at(type);
}

void Game::run() {
    while (_running) {
        if (_framelimit.checkDelay())
            runSystems();
    }
}
