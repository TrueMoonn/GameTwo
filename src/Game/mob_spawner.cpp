/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#include "Game.hpp"

void Game::setMobSpawner() {
    createSystem([this](ECS::Registry&){
        static te::Timestamp delta(1.0f);

        if (!delta.checkDelay())
            return;
        // createEntity(ECS::Entity e, const std::string &name)
    });
};
