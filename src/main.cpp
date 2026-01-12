/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** main.cpp
*/

#include "NetworkMenu.hpp"
#include "Game.hpp"
#include <iostream>

int main() {
    std::string server_ip;
    uint16_t port = 4242;
    std::string username;

    // Show network mode selection menu
    NetworkMode mode = NetworkMenu::showMenu(server_ip, port, username);

    try {
        Game game(mode, server_ip, port, username);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "[Error] Game crashed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}