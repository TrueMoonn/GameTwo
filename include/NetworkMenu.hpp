/*
** EPITECH PROJECT, 2025
** GameTwo
** File description:
** NetworkMenu.hpp - Menu for selecting network mode
*/

#pragma once

#include <string>
#include <cstdint>
#include <iostream>
#include "NetworkMode.hpp"

class NetworkMenu {
 public:
    NetworkMenu() = default;
    ~NetworkMenu() = default;

    /**
     * @brief Display menu and get user's network mode choice
     * @param out_server_ip Output parameter for server IP (if joining)
     * @param out_port Output parameter for port number
     * @param out_username Output parameter for username
     * @return Selected network mode
     */
    static NetworkMode showMenu(std::string& out_server_ip, uint16_t& out_port, std::string& out_username) {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "         GAME TWO - MULTIPLAYER         \n";
        std::cout << "========================================\n";
        std::cout << "\n";
        std::cout << "Select mode:\n";
        std::cout << "  1. Solo (single player)\n";
        std::cout << "  2. Host (multiplayer server)\n";
        std::cout << "  3. Join (connect to server)\n";
        std::cout << "\n";
        std::cout << "Enter choice (1-3): ";
        
        int choice = 0;
        std::cin >> choice;
        std::cin.ignore();

        // Get username for all modes
        std::cout << "Enter your username: ";
        std::getline(std::cin, out_username);
        if (out_username.empty()) {
            out_username = "Player";
        }

        switch (choice) {
            case 1:
                std::cout << "\n[Starting Solo Mode]\n";
                return NetworkMode::SOLO;
                
            case 2: {
                std::cout << "\n[Starting Host Mode]\n";
                std::cout << "Enter port (default 4242): ";
                std::string port_str;
                std::getline(std::cin, port_str);
                
                if (port_str.empty()) {
                    out_port = 4242;
                } else {
                    try {
                        out_port = static_cast<uint16_t>(std::stoi(port_str));
                    } catch (...) {
                        out_port = 4242;
                    }
                }
                
                std::cout << "Hosting on port: " << out_port << "\n";
                std::cout << "Players can join by connecting to your IP address\n";
                return NetworkMode::HOST;
            }
                
            case 3: {
                std::cout << "\n[Starting Client Mode]\n";
                std::cout << "Enter server IP (default 127.0.0.1): ";
                std::getline(std::cin, out_server_ip);
                
                if (out_server_ip.empty()) {
                    out_server_ip = "127.0.0.1";
                }
                
                std::cout << "Enter port (default 4242): ";
                std::string port_str;
                std::getline(std::cin, port_str);
                
                if (port_str.empty()) {
                    out_port = 4242;
                } else {
                    try {
                        out_port = static_cast<uint16_t>(std::stoi(port_str));
                    } catch (...) {
                        out_port = 4242;
                    }
                }
                
                std::cout << "Connecting to " << out_server_ip << ":" << out_port << "\n";
                return NetworkMode::CLIENT;
            }
                
            default:
                std::cout << "Invalid choice, starting Solo mode\n";
                return NetworkMode::SOLO;
        }
    }
};