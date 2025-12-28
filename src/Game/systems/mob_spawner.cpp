/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_spawner.cpp
*/

#include <ECS/DenseZipper.hpp>
#include <maths/Vector.hpp>

#include <physic/components/position.hpp>
#include <interaction/components/player.hpp>
#include <entity_spec/components/damage.hpp>
#include <entity_spec/components/health.hpp>

#include "ECS/DenseSA.hpp"
#include "Game/systems.hpp"

void mobSpawner(Game& game) {
    game.createSystem([&game](ECS::Registry&){
        static te::Timestamp delta(5.0f);
        if (!delta.checkDelay())
            return;

        game.updateDifficulty(1.2);
        float diff = game.getDifficulty();
        auto& players = game.getComponent<addon::intact::Player>();
        auto& positions = game.getComponent<addon::physic::Position2>();
        auto& healths = game.getComponent<addon::eSpec::Health>();
        auto& damages = game.getComponent<addon::eSpec::Damage>();

        std::size_t r = 600;
        for (auto&& [_, pos] : ECS::DenseZipper(players, positions)) {
            for (std::size_t i = 0; i < diff; ++i) {
                float a = std::rand() % 361;
                std::size_t entity = game.nextEntity(MOB);
                mat::Vector2f npos =
                    {pos.x + r * std::sin(a), pos.y + r * std::cos(a)};
                game.createEntity(entity, "fire_skull", npos);
                GET_ENTITY_CMPT(healths, entity).amount *= diff;
                GET_ENTITY_CMPT(damages, entity).amount *= diff;
            }
        }
    });
};
