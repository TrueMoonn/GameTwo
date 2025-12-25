/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#include <physic/components/position.hpp>

#include "ECS/DenseZipper.hpp"
#include "Game/components/spawner.hpp"

#include "Game/systems.hpp"

void mobSpawner(Game& game) {
    game.createSystem([&game](ECS::Registry&){
        static te::Timestamp delta(5.0f);

        if (!delta.checkDelay())
            return;
        auto& spawners = game.getComponent<Spawner>();
        auto& positions = game.getComponent<addon::physic::Position2>();

        for (auto&& [spa, pos] : ECS::DenseZipper(spawners, positions)) {
            if (spa.active) {
                game.createEntity(game.nextEntity(MOB), spa.entity_name, pos);
            }
        }
    });
};
