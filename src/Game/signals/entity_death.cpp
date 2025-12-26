/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** entity_death.cpp
*/

#include <toml++/toml.hpp>
#include <ECS/Entity.hpp>
#include <ECS/DenseSA.hpp>

#include <entity_spec/components/timeout.hpp>
#include <physic/components/position.hpp>
#include <display/components/animation.hpp>
#include <entity_spec/components/health.hpp>

#include "Game.hpp"

void deathAnimation(Game& game) {
    game.sub<ECS::Entity>("no_health_entity", [&game](ECS::Entity e) {
        auto pos =
            GET_ENTITY_CMPT(game.getComponent<addon::physic::Position2>(), e);
        game.removeEntity(e);
        game.createEntity(e, "fire_skull_dead", pos);
    });
}

void killTimeout(Game& game) {
    game.sub<ECS::Entity>("timout_entity", [&game](ECS::Entity e) {
        game.removeEntity(e);
    });
}
