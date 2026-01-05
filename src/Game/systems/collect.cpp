/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** collect.cpp
*/

#include <cmath>

#include <ECS/DenseZipper.hpp>
#include <maths/Vector.hpp>
#include <interaction/components/player.hpp>
#include <physic/components/position.hpp>
#include <physic/components/velocity.hpp>

#include "Game/components/collectible.hpp"
#include "Game/components/xp.hpp"
#include "Game/systems.hpp"

void collectXp(Game& game) {
    game.createSystem([&game](ECS::Registry&) {
        auto& positions = game.getComponent<addon::physic::Position2>();
        auto& velocities = game.getComponent<addon::physic::Velocity2>();
        auto& players = game.getComponent<addon::intact::Player>();
        auto& exps = game.getComponent<Xp>();
        auto& collectibles = game.getComponent<Collectible>();

        for (auto&& [_, ppos, pxp] : ECS::DenseZipper(players, positions, exps)) {
            for (auto&& [e, xp, xpos, xvel, _] : ECS::IndexedDenseZipper(
                exps, positions, velocities, collectibles)) {
                float dist = std::sqrt(std::pow(xpos.x - ppos.x, 2) +
                    std::pow(xpos.y - ppos.y, 2));
                if (dist < 150) {
                    mat::Vector2f dir(ppos - xpos);
                    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                    dir /= length;
                    xvel.x += dir.x * dist;
                    xvel.y += dir.y * dist;
                    xvel *= 0.95;
                }
                if (dist < 30 &&
                    std::sqrt(std::pow(xvel.x, 2) + std::pow(xvel.y, 2)) < 100) {
                    pxp.amount += xp.amount;
                    game.removeEntity(e);
                }
            }
        }
    });
}
