//
// Created by bswenson3 on 11/9/16.
//

#include "Game.h"

Game::Game() :
    m_window(sf::VideoMode(640, 1000), "Cool Game")
{
    //load the player
    m_player.load("dragon.png",288,288,96,96);
    m_fire.load("fire.png",0,128,64,64);
    m_fire2.load("fire.png",0,128,64,64);
    m_Snake.load("Snake.png",0,0,200,150);

    m_player.setPosition(219,800);
    m_Snake.setPosition(219,25);


    //size him.  trial and error to get correct values
    m_player.setScale(2.0f);
    m_fire.setScale(2.0f);
    m_fire2.setScale(2.0f);



}

void Game::run() {
    sf::Clock clock;
    sf::Clock animatorClock;
    sf::Clock fireClock;
    sf::Clock fireClock2;



    while(m_window.isOpen()) {
        sf::Vector2f position = m_player.getPosition();


        if (fireClock.getElapsedTime().asSeconds() < 0.1) {
            m_fire.setPosition(position.x + 30, position.y - 75);
        }
        if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock2.getElapsedTime().asSeconds() < 0.15) {
            m_fire2.setPosition(position.x + 30, position.y - 75);
        }
        if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock.getElapsedTime().asSeconds() < 0.5) {
            m_fire.move(sf::Vector2f(0, -15));
        }
        if (fireClock2.getElapsedTime().asSeconds() > 0.15 && fireClock2.getElapsedTime().asSeconds() < 0.55) {
            m_fire2.move(sf::Vector2f(0, -15));
        }
        if (fireClock.getElapsedTime().asSeconds() > 0.5) {
            fireClock.restart();
        }
        if (fireClock2.getElapsedTime().asSeconds() > 0.55) {
            fireClock2.restart();
        }









        if(animatorClock.getElapsedTime().asSeconds() < 0.1) {
            m_player.load("dragon.png",0,288,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.1 && animatorClock.getElapsedTime().asSeconds() < 0.2) {
            m_player.load("dragon.png",96,288,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.2 && animatorClock.getElapsedTime().asSeconds() < 0.3) {
            m_player.load("dragon.png",192,288,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.3 && animatorClock.getElapsedTime().asSeconds() < 0.4) {
            m_player.load("dragon.png",288,288,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.4) {
            animatorClock.restart();
        }
        //std::cout << position.x << "," << position.y << std::endl;
        sf::Time deltaT = clock.restart();
        processEvents();
        update(deltaT);
        render();
    }

}

void Game::processEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed:
            //handle key down here
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                m_window.close();
                break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isDown) {
    if(key == sf::Keyboard::Left)
        m_left = isDown;
    if(key == sf::Keyboard::Right)
        m_right = isDown;
//    if(key == sf::Keyboard::Up)
//        m_up = isDown;
//    if(key == sf::Keyboard::Down)
//        m_down = isDown;
}

//use time since last update to get smooth movement
void Game::update(sf::Time deltaT) {
    //Look a vector class!
    sf::Vector2f movement(0.0f, 0.0f);
    if(m_up)
        movement.y -= m_speed;
    if(m_down)
        movement.y += m_speed;
    if(m_left)
        movement.x -= m_speed;
    if(m_right)
        movement.x += m_speed;

    m_player.move(movement * deltaT.asSeconds());

}

void Game::render() {
    m_window.clear();
    m_player.draw(m_window);
    m_fire.draw(m_window);
    m_fire2.draw(m_window);
    m_Snake.draw(m_window);


    m_window.display();
}