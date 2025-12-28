/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** xp.hpp
*/

#pragma once

    #include "Game.hpp"

struct Xp {
    Xp(int, int);

    int amount;
    int level;
};

void xpComponent(Game& game);
