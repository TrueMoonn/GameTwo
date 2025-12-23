/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** main.cpp
*/

#include <GameTool.hpp>
#include <events.hpp>
#include <clock.hpp>

#include "configs.hpp"
#include "entities.hpp"
#include "player.hpp"

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
    gtool.createMap(eField::MAP_BEGIN, 0);
    gtool.createEntity(eField::PLAYER, "player",
        {36.f * 50 / 2, 36.f * 50 / 2});

    playerMovementsSubscription(gtool);

    bool running = true;
    gtool.sub("closed", [&running]() {running = false;});
    te::Timestamp delta(1.0f / 60);
    while (running) {
        if (delta.checkDelay())
            gtool.runSystems();
    }
    return 0;
}
