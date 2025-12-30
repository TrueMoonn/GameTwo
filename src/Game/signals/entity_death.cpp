/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** entity_death.cpp
*/

#include <toml++/toml.hpp>
#include <ECS/Entity.hpp>
#include <ECS/DenseSA.hpp>

#include <physic/components/position.hpp>

#include "Game/components/mob.hpp"
#include "Game.hpp"

void deathAnimation(Game& game) {
    game.sub<ECS::Entity>("no_health_entity", [&game](ECS::Entity e) {
        auto pos =
            GET_ENTITY_CMPT(game.getComponent<addon::physic::Position2>(), e);
        if (game.getComponent<Mob>().hasComponent(e)) {
            game.createEntity(game.nextEntity(XP), "xp", {pos.x - 8, pos.y});
            game.removeEntity(e);
            game.createEntity(e, "fire_skull_dead", pos);
        } else {
            game.removeEntity(e);
        }
    });
}

void killTimeout(Game& game) {
    game.sub<ECS::Entity>("timout_entity", [&game](ECS::Entity e) {
        game.removeEntity(e);
    });
}
