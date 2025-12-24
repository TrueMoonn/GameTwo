/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#include <physic/components/position.hpp>

#include "ECS/DenseZipper.hpp"
#include "components/spawner.hpp"

#include "Game.hpp"

void Game::setMobSpawner() {
    registerComponent<Spawner>();
    createSystem([this](ECS::Registry&){
        static te::Timestamp delta(1.0f);

        if (!delta.checkDelay())
            return;
        auto& spawners = getComponent<Spawner>();
        auto& positions = getComponent<addon::physic::Position2>();

        for (auto&& [spa, pos] : ECS::DenseZipper(spawners, positions)) {
            if (spa.active) {
                createEntity(nextEntity(MOB), spa.entity_name, pos);
            }
        }
    });
};
