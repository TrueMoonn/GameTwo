/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** weapons.hpp
*/

#pragma once

    #include <functional>
    #include <string>
    #include <unordered_map>

    #include <maths/Vector.hpp>

    #include "Game.hpp"

enum Weapon_e {
    SWORD = 0,
    BOW,
};

static const std::unordered_map<Weapon_e, std::string> WEAPONS_NAME = {
    {SWORD, "sword"},
    {BOW, "bow"}
};

void swordWeapon(Game&, int, ECS::Entity);
void bowWeapon(Game&, int, ECS::Entity);

static const std::unordered_map<std::string,
    std::function<void(Game&, int, ECS::Entity)>> WEAPONS = {
    {WEAPONS_NAME.at(SWORD), &swordWeapon},
    {WEAPONS_NAME.at(BOW), &bowWeapon},
};
