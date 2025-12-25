/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_mov.cpp
*/

#include <cmath>

#include <ECS/DenseZipper.hpp>
#include <maths/Vector.hpp>
#include <interaction/components/player.hpp>
#include <physic/components/position.hpp>
#include <physic/components/velocity.hpp>

#include "Game/components/mob.hpp"
#include "Game/systems.hpp"

void mobMovement(Game& game) {
    game.createSystem([&game](ECS::Registry&){
        auto& players = game.getComponent<addon::intact::Player>();
        auto& positions = game.getComponent<addon::physic::Position2>();
        auto& velocities = game.getComponent<addon::physic::Velocity2>();

        for (auto&& [_, pos] : ECS::DenseZipper(players, positions)) {
            auto& mobs = game.getComponent<Mob>();

            for (auto&& [mob, mpos, mvel] :
                ECS::DenseZipper(mobs, positions, velocities)) {
                mat::Vector2f dir(pos - mpos);
                float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                dir /= length;
                mvel.x = dir.x * mob.speed;
                mvel.y = dir.y * mob.speed;
            }
        }
    });
}
