/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** bow.cpp
*/

#include <clock.hpp>
#include <maths/Vector.hpp>
#include <ECS/Entity.hpp>
#include <ECS/DenseSA.hpp>
#include <ECS/DenseZipper.hpp>
#include <physic/components/position.hpp>
#include <physic/components/velocity.hpp>
#include <iostream>
#include <map>

#include "Game/components/mob.hpp"
#include "entities.hpp"
#include "weapons.hpp"

static mat::Vector2f foundClosestMob(Game& game, mat::Vector2f ppos) {
    auto& positions = game.getComponent<addon::physic::Position2>();
    auto& mobs = game.getComponent<Mob>();
    float minDist = 500.f;
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
    
    // Avoid division by zero - if no mob found or too close, shoot right
    if (length < 0.01f) {
        return {1.0f, 0.0f};
    }
    
    dir /= length;
    return dir;
}

void bowWeapon(Game& game, int level, ECS::Entity player) {
    // Use per-player cooldown instead of global static
    static std::map<ECS::Entity, te::Timestamp> player_cooldowns;
    
    // Initialize cooldown for new players
    if (player_cooldowns.find(player) == player_cooldowns.end()) {
        player_cooldowns.emplace(player, te::Timestamp(1.0f));
        std::cout << "[bowWeapon] Initialized cooldown for player " << player << std::endl;
    }
    
    auto& cooldown = player_cooldowns.at(player);
    if (!cooldown.checkDelay())
        return;

    auto& velocities = game.getComponent<addon::physic::Velocity2>();
    auto& ppos = GET_ENTITY_CMPT(
        game.getComponent<addon::physic::Position2>(), player);
    mat::Vector2f direction = foundClosestMob(game, ppos);
    
    // Debug: log when bow fires
    std::cout << "[bowWeapon] Player " << player << " firing arrow at (" 
              << ppos.x << ", " << ppos.y << ") direction=(" 
              << direction.x << ", " << direction.y << ")" << std::endl;

    ECS::Entity arrow = game.nextEntity(WEAPON);
    game.createEntity(arrow, "bow", ppos);
    auto& avel = GET_ENTITY_CMPT(velocities, arrow);
    avel.x = direction.x * 300;
    avel.y = direction.y * 300;
    
    std::cout << "[bowWeapon] Created arrow entity " << arrow 
              << " for player " << player << std::endl;
}
