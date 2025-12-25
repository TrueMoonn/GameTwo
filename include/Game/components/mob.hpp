/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob.hpp
*/

#pragma once

    #include "Game.hpp"

struct Mob {
    explicit Mob(float);

    float speed;
};

void mobComponent(Game& game);
