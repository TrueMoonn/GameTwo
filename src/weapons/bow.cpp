/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** bow.cpp
*/

#include <clock.hpp>
#include <ECS/DenseSA.hpp>
#include <ECS/DenseZipper.hpp>
#include <physic/components/position.hpp>
#include <maths/Vector.hpp>

#include "ECS/Entity.hpp"
#include "Game/components/mob.hpp"
#include "entities.hpp"
#include "physic/components/velocity.hpp"
#include "weapons.hpp"

static mat::Vector2f foundClosestMob(Game& game, mat::Vector2f ppos) {
    auto& positions = game.getComponent<addon::physic::Position2>();
    auto& mobs = game.getComponent<Mob>();
    float minDist = 2000.f;
    mat::Vector2f dir = {0, 0};
    for (auto&& [_, mpos] : ECS::DenseZipper(mobs, positions)) {
        float dist = std::sqrt(std::pow(mpos.x - ppos.x, 2) +
            std::pow(mpos.y - ppos.y, 2));
        if (dist < minDist) {
            minDist = dist;
            dir = mpos - ppos;
        }
    }
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    dir /= length;
    return dir;
}

void bowWeapon(Game& game, int level, ECS::Entity player) {
    static te::Timestamp delta(1.0f);
    if (!delta.checkDelay())
        return;

    auto& velocities = game.getComponent<addon::physic::Velocity2>();
    auto& ppos = GET_ENTITY_CMPT(
        game.getComponent<addon::physic::Position2>(), player);
    mat::Vector2f direction = foundClosestMob(game, ppos);

    ECS::Entity arrow = game.nextEntity(WEAPON);
    game.createEntity(arrow, "bow", ppos);
    auto& avel = GET_ENTITY_CMPT(velocities, arrow);
    avel.x = direction.x * 200;
    avel.y = direction.y * 200;
}
