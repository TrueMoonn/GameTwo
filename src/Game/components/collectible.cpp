/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** collectible.cpp
*/

#include "Game/components/collectible.hpp"

void collectibleComponent(Game &game) {
    game.registerComponent<Collectible>("collectible",
        [&game](ECS::Entity e, const toml::table&) {
        game.createComponent<Collectible>(e);
    });
}
