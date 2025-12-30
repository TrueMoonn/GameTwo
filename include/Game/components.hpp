/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** components.hpp
*/

#pragma once

    #include <vector>
    #include <functional>

    #include "Game/components/collectible.hpp"
    #include "Game/components/spawner.hpp"
    #include "Game/components/mob.hpp"
    #include "Game/components/xp.hpp"
    #include "Game/components/weapons.hpp"

static const std::vector<std::function<void(Game&)>> COMPONENTS {
    &spawnerComponent,
    &mobComponent,
    &xpComponent,
    &collectibleComponent,
    &weaponComponent,
    &weaponsComponent,
};
