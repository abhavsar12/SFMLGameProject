//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>

// Hi there
class Game {
public:
    //use default screen size
    Game();
    //run the game
    void run();

private:
    void processEvents();
    //update the game objects
    void update(sf::Time deltaT);
    //draw the scene
    void render();
    //handle input from the user
    void handlePlayerInput(sf::Keyboard::Key key, bool isDown);

    sf::RenderWindow m_window;

    GameObject m_player;
    GameObject m_background;
    GameObject m_fire;
    GameObject m_fire2;
    GameObject m_Snake;


    //TODO::these should be moved to game object
    float m_speed = 300.0f;
    bool m_left = false;
    bool m_right = false;
    bool m_up = false;
    bool m_down = false;
};


