/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** Game.hpp
*/

#pragma once

    #include <unordered_map>
    #include <memory>

    #include <ECS/Entity.hpp>
    #include <GameTool.hpp>
    #include <clock.hpp>
    #include <network/AutoClient.hpp>
    #include <network/AutoServer.hpp>

    #include "entities.hpp"
    #include "NetworkMode.hpp"

    #define FRAME_LIMIT 1.0f / 60   // 60 fps

class Game : public te::GameTool {
 public:
    Game();
    Game(NetworkMode mode, const std::string& server_ip = "", uint16_t port = 0, const std::string& username = "Player");

    ECS::Entity nextEntity(EntityType type);

    void updateDifficulty(float);
    float getDifficulty() const;

    void run();

    // Multiplayer methods
    bool isMultiplayer() const { return _network_mode != NetworkMode::SOLO; }
    bool isHost() const { return _network_mode == NetworkMode::HOST; }
    bool isClient() const { return _network_mode == NetworkMode::CLIENT; }
    NetworkMode getNetworkMode() const { return _network_mode; }

    // Get player ID for current client
    std::uint32_t getLocalPlayerId() const;

    // Send inputs to server (client mode only)
    void sendInputsToServer(const te::Keys& keys);

 private:
    void initSolo();
    void initHost(uint16_t port);
    void initClient(const std::string& server_ip, uint16_t port, const std::string& username);
    void setupNetworkCallbacks();

    float _difficulty;
    bool _running;
    te::Timestamp _framelimit;
    std::unordered_map<EntityType, ECS::Entity> _nextEntities;

    // Networking
    NetworkMode _network_mode;
    std::unique_ptr<net::AutoServer> _server;
    std::unique_ptr<net::AutoClient> _client;
    std::string _username;
    std::uint32_t _local_player_id;
};
