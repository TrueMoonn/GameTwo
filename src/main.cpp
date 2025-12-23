/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** main.cpp
*/

#include <events.hpp>
#include <GameTool.hpp>

#include <ECS/DenseZipper.hpp>
#include <interaction/components/player.hpp>
#include <physic/components/velocity.hpp>
#include <clock.hpp>

#include "configs.hpp"
#include "entities.hpp"

int main() {
    te::GameTool gtool;
    gtool.loadPlugins();

    for (auto& sys : SYSTEMS_NAME)
        gtool.createSystem(sys);
    for (auto& conf : CONFIG_PATHS)
        gtool.addConfig(conf);
    for (auto& map : MAP_PATHS)
        gtool.addMap(map);

    gtool.createComponent("window", eField::SYSTEM);
    ECS::Entity last = gtool.createMap(MAP_BEGIN, 0);

    gtool.createEntity(PLAYER, "player", {100.f, 100.f});
    gtool.sub<te::Keys>("key_input", [&gtool](te::Keys keys){
        auto& players = gtool.getComponent<addon::intact::Player>();
        auto& velocities = gtool.getComponent<addon::physic::Velocity2>();

        for (auto &&[_, vel] : ECS::DenseZipper(players, velocities)) {
            if (keys[te::Key::Z]) {
                vel.y = -170.0;
            } else if (keys[te::Key::S]) {
                vel.y = 170.0;
            } else {
                vel.y = 0.0;
            }
            if (keys[te::Key::Q]) {
                vel.x = -170.0;
            } else if (keys[te::Key::D]) {
                vel.x = 170.0;
            } else {
                vel.x = 0.0;
            }
        }
    });

    bool running = true;
    gtool.sub("closed", [&running]() {running = false;});
    te::Timestamp delta(1.0f / 60);
    while (running) {
        if (delta.checkDelay())
            gtool.runSystems();
    }
    return 0;
}
