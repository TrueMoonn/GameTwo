/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** components.hpp
*/

#pragma once

    #include <vector>

    #include "Game/components/spawner.hpp"
    #include "Game/components/mob.hpp"

static const std::vector<std::function<void(Game&)>> COMPONENTS {
    &spawnerComponent,
    &mobComponent,
};
