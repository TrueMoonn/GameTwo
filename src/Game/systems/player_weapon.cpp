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
    game.createSystem("player_weapon", [&game](ECS::Registry&) {
        // Only fire weapons on server/host or in solo mode
        // Client receives projectile states from server
        if (game.isClient()) {
            return;
        }
        
        auto& player = game.getComponent<addon::intact::Player>();
        auto& positions = game.getComponent<addon::physic::Position2>();
        auto& weapons = game.getComponent<Weapons>();

        static int call_count = 0;
        call_count++;
        
        int player_count = 0;
        for (auto&& [e, pl, wps, pos] :
            ECS::IndexedDenseZipper(player, weapons, positions)) {
            player_count++;
            if (call_count % 60 == 0) {
                std::cout << "[playerWeapon] Entity " << e << " (player " << pl.player 
                          << ") has " << wps.list.size() << " weapons at (" 
                          << pos.x << ", " << pos.y << ")" << std::endl;
            }
            for (const auto& wp : wps.list) {
                WEAPONS.at(wp.name)(game, wp.level, e);
            }
        }
        
        if (call_count % 60 == 0) {
            std::cout << "[playerWeapon] Processed " << player_count << " players with weapons" << std::endl;
        }
    });
}
