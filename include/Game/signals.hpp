/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** signals.cpp
*/

#pragma once

    #include <vector>

    #include "Game.hpp"

void playerMovement(Game& game);

static const std::vector<std::function<void(Game&)>> SIGNALS {
    &playerMovement,
};
