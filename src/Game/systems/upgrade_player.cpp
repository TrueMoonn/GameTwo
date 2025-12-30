/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** upgrade_player.hpp
*/

#include <ECS/DenseSA.hpp>
#include <ECS/DenseZipper.hpp>
#include <interaction/components/player.hpp>

#include "player.hpp"
#include "Game/components/xp.hpp"
#include "Game/systems.hpp"

void upgradePlayer(Game& game) {
    game.createSystem([&game](ECS::Registry&) {
        auto& player = game.getComponent<addon::intact::Player>();
        auto& xps = game.getComponent<Xp>();

        for (auto&& [_, xp] : ECS::DenseZipper(player, xps)) {
            if (xp.amount > XP_TO_LVL_UP(xp.level)) {
                xp.level += 1;
                xp.amount = 0;
            }
        }
    });
}
