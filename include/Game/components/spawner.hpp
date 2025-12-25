/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#pragma once

    #include <string>

    #include "Game.hpp"

struct Spawner {
    Spawner(const std::string& name, bool activity = false);
    Spawner(const Spawner&) = default;
    Spawner& operator=(const Spawner&) = default;
    Spawner(Spawner&&) = default;
    Spawner& operator=(Spawner&&) = default;

    std::string entity_name;
    bool active;
};

void spawnerComponent(Game& game);
