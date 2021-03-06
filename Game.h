//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <SFML/Network.hpp>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>


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
    void renderTitle();
    void renderStory1();
    void renderStory2();
    void renderEndGame();
    //draw the title
    void render();
    //handle input from the user
    void handlePlayerInput(sf::Keyboard::Key key, bool isDown);
    void setupServer();
    void setupClient();
    void renderWinGame();

    sf::RenderWindow m_window;

    GameObject m_player;
    GameObject m_player2;
    GameObject m_background;
    GameObject m_backgroundFiller;
    GameObject m_fire;
    GameObject m_fire2;
    GameObject m_fire3;
    GameObject m_fire4;
    GameObject m_Snake1;
    GameObject m_Snake2;
    GameObject m_Snake3;
    GameObject m_Snake4;
    GameObject m_endGame;
    GameObject m_titleSlide;
    GameObject m_Story1;
    GameObject m_Story2;
    sf::Text text;
    sf::Text text2;
    sf::Text text3;
    sf::Text highscoretext;
    sf::RectangleShape line;
    bool server;
    int score1, score2, sockfd, newsockfd, err, dragonposition, snake1xposition, snake1yposition, snake2xposition, snake2yposition, highScore, state;
    int renderCounter = 0;
    int buf = 600;
    char buf2[4];
    int result =0;
    bool gameOver;
    bool p2Win;
    bool sending = true;


    //TCP Stuff
    sf::TcpSocket socket;
    char buffer[255];
    std::size_t received;

    //TODO::these should be moved to game object
    float m_speed = 300.0f;
    bool m_left = false;
    bool m_right = false;
    bool m_up = false;
    bool m_down = false;
};


