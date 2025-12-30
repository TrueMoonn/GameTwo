/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** player_weapon.hpp
*/

#include <ECS/DenseZipper.hpp>
#include <interaction/components/player.hpp>
#include <physic/components/position.hpp>

#include "Game/components/weapons.hpp"
#include "weapons.hpp"
#include "Game/systems.hpp"

void playerWeapon(Game& game) {
    game.createSystem([&game](ECS::Registry&) {
        auto& player = game.getComponent<addon::intact::Player>();
        auto& positions = game.getComponent<addon::physic::Position2>();
        auto& weapons = game.getComponent<Weapons>();

        for (auto&& [e, _, wps, pos] :
            ECS::IndexedDenseZipper(player, weapons, positions)) {
            for (const auto& wp : wps.list) {
                WEAPONS.at(wp.name)(game, wp.level, e);
            }
        }
    });
}
