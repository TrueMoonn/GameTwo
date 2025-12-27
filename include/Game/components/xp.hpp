/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** xp.hpp
*/

#pragma once

    #include "Game.hpp"

struct Xp {
    explicit Xp(int);

    int amount;
};

void xpComponent(Game& game);
