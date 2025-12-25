/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob.cpp
*/

#include "Game/components/mob.hpp"

Mob::Mob(float speed) : speed(speed) {}

void mobComponent(Game &game) {
    game.registerComponent<Mob>("mob",
        [&game](ECS::Entity e, const toml::table& params){
        float speed = params["speed"].value_or(0.f);
        game.createComponent<Mob>(e, speed);
    });
}
