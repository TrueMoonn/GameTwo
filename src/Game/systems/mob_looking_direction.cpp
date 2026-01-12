/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** mob_looking_direction.hpp
*/

#include <ECS/DenseZipper.hpp>
#include <physic/components/velocity.hpp>
#include <sfml/components/sprite.hpp>

#include "Game/components/mob.hpp"
#include "Game/systems.hpp"

void mobLookingDirection(Game& game) {
    game.createSystem("mob_looking_direction", [&game](ECS::Registry&){
        auto& velocities = game.getComponent<addon::physic::Velocity2>();
        auto& sprites = game.getComponent<addon::sfml::Sprite>();
        auto& mobs = game.getComponent<Mob>();

        for (auto&& [_, vel, sp] :
            ECS::DenseZipper(mobs, velocities, sprites)) {
            auto scale = sp.sp.getScale();
            if (vel.x < 0 && scale.x > 0) {
                scale.x *= -1;
                sp.sp.setScale(scale);
            } else if (vel.x > 0 && scale.x < 0) {
                scale.x *= -1;
                sp.sp.setScale(scale);
            }
        }
    });
}
