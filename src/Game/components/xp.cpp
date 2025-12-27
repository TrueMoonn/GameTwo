/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** xp.cpp
*/

#include "Game/components/xp.hpp"

Xp::Xp(int amount) : amount(amount) {}

void xpComponent(Game &game) {
    game.registerComponent<Xp>("xp",
        [&game](ECS::Entity e, const toml::table& params){
        int amount = params["amount"].value_or(0);
        game.createComponent<Xp>(e, amount);
    });
}
