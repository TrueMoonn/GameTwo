/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** Game.hpp
*/

#pragma once

    #include <GameTool.hpp>
    #include <clock.hpp>

    #define FRAME_LIMIT 1.0f / 60   // 60 fps

class Game : public te::GameTool {
 public:
    Game();

    void setPlayerMovement();
    void setMobSpawner();

    void run();

 private:
    bool _running;
    te::Timestamp _framelimit;
};
