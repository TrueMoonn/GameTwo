/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#pragma once

    #include <string>

struct Spawner {
    Spawner() = default;
    Spawner(const Spawner&) = default;
    Spawner& operator=(const Spawner&) = default;
    Spawner(Spawner&&) = default;
    Spawner& operator=(Spawner&&) = default;

    std::string entity_name = "";
    bool active = false;
};
