/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** systems.hpp
*/

#pragma once

    #include <vector>

    #include "Game.hpp"

void mobMovement(Game& game);
void mobSpawner(Game& game);
void mobLookingDirection(Game& game);
void collectXp(Game& game);

static const std::vector<std::function<void(Game&)>> SYSTEMS {
    &mobSpawner,
    &mobMovement,
    &mobLookingDirection,
    &collectXp,
};
