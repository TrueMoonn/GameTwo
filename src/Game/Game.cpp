/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** Game.cpp
*/

#include "ECS/Entity.hpp"
#include "Game/components.hpp"
#include "Game/signals.hpp"
#include "Game/systems.hpp"
#include "configs.hpp"
#include "entities.hpp"
#include "Game.hpp"
#include "interaction/components/player.hpp"
#include "physic/components/position.hpp"
#include "Network/generated_messages.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <typeinfo>

Game::Game() : _framelimit(FRAME_LIMIT), _network_mode(NetworkMode::SOLO), _local_player_id(1) {
    initSolo();
}

Game::Game(NetworkMode mode, const std::string& server_ip, uint16_t port, const std::string& username)
    : _framelimit(FRAME_LIMIT), _network_mode(mode), _username(username), _local_player_id(0) {

    switch (mode) {
        case NetworkMode::SOLO:
            initSolo();
            break;
        case NetworkMode::HOST:
            initHost(port);
            break;
        case NetworkMode::CLIENT:
            initClient(server_ip, port, username);
            break;
    }
}

void Game::initSolo() {
    loadPlugins();
    _difficulty = 1.f;
    std::srand(std::time(0));

    for (auto& func : SYSTEMS)
        func(*this);
    for (auto& sys : PLUGIN_SYSTEMS)
        createSystem(sys);

    for (auto& func : COMPONENTS)
        func(*this);
    for (auto& func : SIGNALS)
        func(*this);
    for (auto& conf : CONFIG_PATHS)
        addConfig(conf);
    for (auto& map : MAP_PATHS)
        addMap(map);

    _nextEntities[EntityType::SYSTEM] = eField::SYSTEM_F;
    _nextEntities[EntityType::PLAYER] = eField::PLAYER_BEGIN;
    _nextEntities[EntityType::MENU] = eField::MENU_BEGIN;
    _nextEntities[EntityType::HUD] = eField::HUD_BEGIN;
    _nextEntities[EntityType::WEAPON] = eField::WEAPON_BEGIN;
    _nextEntities[EntityType::MAP] = eField::MAP_BEGIN;
    _nextEntities[EntityType::MOB] = eField::MOB_BEGIN;
    _nextEntities[EntityType::XP] = eField::XP_BEGIN;

    _nextEntities.at(MAP) = createMap(nextEntity(MAP), 0) + 1;
    ECS::Entity player_entity = nextEntity(PLAYER);
    createEntity(player_entity, "player", {36.f * 50 / 2, 36.f * 50 / 2});

    try {
        createComponent("camera_target", player_entity);
    } catch (const std::exception& e) {
        std::cerr << "[Game] Failed to add CameraTarget: " << e.what() << std::endl;
    }

    createComponent("window", nextEntity(SYSTEM));
    sub("closed", [this]() {_running = false;});
    _running = true;
}

void Game::initHost(uint16_t port) {
    loadPlugins();
    _difficulty = 1.f;
    std::srand(std::time(0));

    for (auto& func : SYSTEMS)
        func(*this);
    for (auto& sys : PLUGIN_SYSTEMS)
        createSystem(sys);

    for (auto& func : COMPONENTS)
        func(*this);
    for (auto& func : SIGNALS)
        func(*this);
    for (auto& conf : CONFIG_PATHS)
        addConfig(conf);
    for (auto& map : MAP_PATHS)
        addMap(map);

    _nextEntities[EntityType::SYSTEM] = eField::SYSTEM_F;
    _nextEntities[EntityType::PLAYER] = eField::PLAYER_BEGIN;
    _nextEntities[EntityType::MENU] = eField::MENU_BEGIN;
    _nextEntities[EntityType::HUD] = eField::HUD_BEGIN;
    _nextEntities[EntityType::WEAPON] = eField::WEAPON_BEGIN;
    _nextEntities[EntityType::MAP] = eField::MAP_BEGIN;
    _nextEntities[EntityType::MOB] = eField::MOB_BEGIN;
    _nextEntities[EntityType::XP] = eField::XP_BEGIN;

    _nextEntities.at(MAP) = createMap(nextEntity(MAP), 0) + 1;

    _server = std::make_unique<net::AutoServer>(getRegistry(), getSignalManager(), port, "UDP");
    _server->setDefaultSpawnPosition(36.f * 50 / 2, 36.f * 50 / 2);
    _server->setDefaultPlayerHealth(100);

    if (!_server->start()) {
        std::cerr << "[Game] Failed to start server!" << std::endl;
        _running = false;
        return;
    }
    setupNetworkCallbacks();

    _local_player_id = 1;
    createEntity(_local_player_id, "player", {36.f * 50 / 2, 36.f * 50 / 2});

    try {
        auto& players = getComponent<addon::intact::Player>();
        auto& player_index_opt = players.getSpar()[PAGE(_local_player_id)][PAGE_INDEX(_local_player_id)];
        if (player_index_opt.has_value()) {
            auto& player_comp = players.getComponent(player_index_opt.value());
            player_comp.player = _local_player_id;
        }
    } catch (const std::exception& e) {
        std::cerr << "[Game] Failed to set player ID: " << e.what() << std::endl;
    }

    try {
        createComponent("camera_target", _local_player_id);
    } catch (const std::exception& e) {
        std::cerr << "[Game] Failed to add CameraTarget: " << e.what() << std::endl;
    }

    createComponent("window", nextEntity(SYSTEM));
    sub("closed", [this]() {_running = false;});
    _running = true;
}

void Game::initClient(const std::string& server_ip, uint16_t port, const std::string& username) {
    loadPlugins();
    _difficulty = 1.f;
    std::srand(std::time(0));

    for (auto& func : SYSTEMS)
        func(*this);
    for (auto& sys : PLUGIN_SYSTEMS) {
        if (sys == "deal_damage" || sys == "kill_timeout") {
            continue;
        }
        createSystem(sys);
    }

    for (auto& func : COMPONENTS)
        func(*this);
    for (auto& func : SIGNALS)
        func(*this);
    for (auto& conf : CONFIG_PATHS)
        addConfig(conf);
    for (auto& map : MAP_PATHS)
        addMap(map);

    _nextEntities[EntityType::SYSTEM] = eField::SYSTEM_F;
    _nextEntities[EntityType::PLAYER] = eField::PLAYER_BEGIN;
    _nextEntities[EntityType::MENU] = eField::MENU_BEGIN;
    _nextEntities[EntityType::HUD] = eField::HUD_BEGIN;
    _nextEntities[EntityType::WEAPON] = eField::WEAPON_BEGIN;
    _nextEntities[EntityType::MAP] = eField::MAP_BEGIN;
    _nextEntities[EntityType::MOB] = eField::MOB_BEGIN;
    _nextEntities[EntityType::XP] = eField::XP_BEGIN;

    _nextEntities.at(MAP) = createMap(nextEntity(MAP), 0) + 1;

    _client = std::make_unique<net::AutoClient>(getRegistry());

    _client->on_logged_in = [this](std::uint32_t player_id) {
        _local_player_id = player_id;

        float spawn_x = 36.f * 50 / 2;
        float spawn_y = 36.f * 50 / 2;
        createEntity(_local_player_id, "player", {spawn_x, spawn_y});

        try {
            auto& players = this->getComponent<addon::intact::Player>();
            auto& player_index_opt = players.getSpar()[PAGE(player_id)][PAGE_INDEX(player_id)];
            if (player_index_opt.has_value()) {
                auto& player_comp = players.getComponent(player_index_opt.value());
                player_comp.player = player_id;
            }
        } catch (const std::exception& e) {
            std::cerr << "[Game] Failed to set player ID: " << e.what() << std::endl;
        }

        try {
            createComponent("camera_target", player_id);
        } catch (const std::exception& e) {
            std::cerr << "[Game] Failed to add CameraTarget: " << e.what() << std::endl;
        }

        _client->player_id_to_entity[player_id] = player_id;
    };

    _client->on_player_discovered = [this](std::uint32_t player_id, float x, float y) {

        if (!std::isfinite(x) || !std::isfinite(y)) {
            std::cerr << "[Game] Player " << player_id << " has invalid coordinates (" << x << ", " << y << "), skipping" << std::endl;
            return;
        }

        if (player_id == _local_player_id) {
            return;
        }

        if (_client->player_id_to_entity.find(player_id) != _client->player_id_to_entity.end()) {
            return;
        }

        createEntity(player_id, "player", {x, y});

        try {
            auto& players = this->getComponent<addon::intact::Player>();
            auto& player_index_opt = players.getSpar()[PAGE(player_id)][PAGE_INDEX(player_id)];
            if (player_index_opt.has_value()) {
                auto& player_comp = players.getComponent(player_index_opt.value());
                player_comp.player = player_id;
            }
        } catch (const std::exception& e) {
            std::cerr << "[Game] Failed to set player ID: " << e.what() << std::endl;
        }

        _client->player_id_to_entity[player_id] = player_id;
    };

    // Callback when discovering enemies
    _client->on_enemy_discovered = [this](std::uint32_t enemy_id, float x, float y) {
        if (!std::isfinite(x) || !std::isfinite(y)) {
            std::cerr << "[Game] Enemy " << enemy_id << " has invalid coordinates (" << x << ", " << y << "), skipping" << std::endl;
            return;
        }

        if (_client->enemy_id_to_entity.find(enemy_id) != _client->enemy_id_to_entity.end()) {
            return;
        }

        ECS::Entity local_entity = nextEntity(MOB);
        createEntity(local_entity, "fire_skull", {x, y});

        _client->enemy_id_to_entity[enemy_id] = local_entity;
    };

    _client->on_projectile_discovered = [this](std::uint32_t proj_id, float x, float y, uint8_t type) {
        if (!std::isfinite(x) || !std::isfinite(y)) {
            return;
        }

        if (_client->projectile_id_to_entity.find(proj_id) != _client->projectile_id_to_entity.end()) {
            return;
        }

        ECS::Entity local_entity;
        if (type == 1) {
            local_entity = nextEntity(XP);
            createEntity(local_entity, "xp", {x, y});
        } else {
            local_entity = nextEntity(WEAPON);
            createEntity(local_entity, "bow", {x, y});
        }

        _client->projectile_id_to_entity[proj_id] = local_entity;
    };

    if (!_client->connectAndLogin(server_ip, port, username)) {
        std::cerr << "[Game] Failed to connect to server!" << std::endl;
        _running = false;
        return;
    }

    int wait_count = 0;
    const int max_wait = 100;
    while (!_client->isLoggedIn() && wait_count < max_wait) {
        _client->update(0.1f);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        wait_count++;
    }

    if (!_client->isLoggedIn()) {
        std::cerr << "[Game] Login timeout - server did not respond!" << std::endl;
        _running = false;
        return;
    }

    for (int i = 0; i < 10; i++) {
        _client->update(0.1f);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Create window component for rendering
    createComponent("window", nextEntity(SYSTEM));
    sub("closed", [this]() {_running = false;});

    _running = true;
}

void Game::setupNetworkCallbacks() {
    if (_server) {
        // Handle player login
        _server->onPlayerLogin([this](std::uint32_t player_id, const std::string& username) {
            if (player_id == 1) {
                return;
            }

            // Create player entity for the new player
            float spawn_x = 36.f * 50 / 2;
            float spawn_y = 36.f * 50 / 2;

            // Offset spawn position slightly for second player
            spawn_x += 50.f;
            spawn_y += 50.f;

            createEntity(player_id, "player", {spawn_x, spawn_y});

            try {
                auto& players = this->getComponent<addon::intact::Player>();
                auto& player_index_opt = players.getSpar()[PAGE(player_id)][PAGE_INDEX(player_id)];
                if (player_index_opt.has_value()) {
                    auto& player_comp = players.getComponent(player_index_opt.value());
                    player_comp.player = player_id;
                }
            } catch (const std::exception& e) {
                std::cerr << "[Game] Failed to set player ID: " << e.what() << std::endl;
            }
        });

        // Handle player logout
        _server->onPlayerLogout([this](std::uint32_t player_id) {
            removeEntity(player_id);
        });

        // Handle client inputs via signal system
        _server->onClientInputs([this](std::uint32_t player_id, const std::string& inputs) {
            // Inputs are automatically emitted as signals by AutoServer
            // No need to do anything here unless custom logic is needed
        });
    }
}

ECS::Entity Game::nextEntity(EntityType type) {
    if (_nextEntities.at(type) > ENTITY_FIELDS.at(type).max) {
        _nextEntities.at(type) = ENTITY_FIELDS.at(type).min;
    } else {
        _nextEntities.at(type) += 1;
    }
    return _nextEntities.at(type);
}

void Game::run() {
    while (_running) {
        try {
            if (_framelimit.checkDelay()) {
                if (_server) {
                    _server->update(FRAME_LIMIT);
                }
                if (_client) {
                    _client->update(FRAME_LIMIT);
                }

                runSystems();
            }
        } catch (const std::bad_optional_access& e) {
            std::cerr << "[Game] FATAL ERROR: bad_optional_access in game loop!" << std::endl;
            std::cerr << "[Game] This usually means a component access failed." << std::endl;
            std::cerr << "[Game] Exception: " << e.what() << std::endl;
            _running = false;
            throw;
        } catch (const std::out_of_range& e) {
            std::cerr << "[Game] FATAL ERROR: out_of_range in game loop!" << std::endl;
            std::cerr << "[Game] Exception: " << e.what() << std::endl;
            _running = false;
            throw;
        } catch (const std::exception& e) {
            std::cerr << "[Game] FATAL ERROR: exception in game loop!" << std::endl;
            std::cerr << "[Game] Exception type: " << typeid(e).name() << std::endl;
            std::cerr << "[Game] Exception: " << e.what() << std::endl;
            _running = false;
            throw;
        } catch (...) {
            std::cerr << "[Game] FATAL ERROR: unknown exception in game loop!" << std::endl;
            _running = false;
            throw;
        }
    }
}

void Game::updateDifficulty(float factor) {
    _difficulty *= factor;
}

float Game::getDifficulty() const {
    return _difficulty;
}

std::uint32_t Game::getLocalPlayerId() const {
    return _local_player_id;
}

void Game::sendInputsToServer(const te::Keys& keys) {
    if (_client && isClient()) {
        _client->sendInputs(keys);
    }
}
