/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** weapons.hpp
*/

#pragma once

    #include <vector>
    #include <string>

    #include "Game.hpp"

struct Weapon {
    Weapon(const std::string&, int);

    std::string name;
    int level;
};

struct Weapons {
    Weapons(const std::vector<Weapon>&);

    std::vector<Weapon> list;
};

void weaponComponent(Game& game);
void weaponsComponent(Game& game);
