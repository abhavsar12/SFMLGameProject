//
// Created by bswenson3 on 11/9/16.
//

#include "Game.h"

Game::Game() :
    m_window(sf::VideoMode(1500, 750), "EverWing")
{
    //load the player
    m_player.load("dragon.png",288,192,96,96);
    m_fire.load("fire.png",0,256,64,64);
    m_fire2.load("fire.png",0,256,64,64);
    m_Snake1.load("Snakes.png",0,0,200,150);
    m_Snake2.load("Snakes.png",0,0,200,150);
    m_background.load("background.png",0,0,1500,750);
    m_backgroundFiller.load("background.png",0,0,1500,750);
    m_backgroundFiller.setPosition(1500,0);


    m_player.setPosition(35,268);
    m_Snake1.setPosition(1500,268);
    m_Snake2.setPosition(1500,600);



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
        sf::Vector2f positionBack = m_background.getPosition();
        sf::Vector2f positionBackFiller = m_backgroundFiller.getPosition();
        sf::Vector2f snake1Position = m_Snake1.getPosition();
        sf::Vector2f snake2Position = m_Snake2.getPosition();

        if (fireClock.getElapsedTime().asSeconds() < 0.1) {
            m_fire.setPosition(position.x + 150, position.y + 75);
        }
        if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock2.getElapsedTime().asSeconds() < 0.15) {
            m_fire2.setPosition(position.x + 150, position.y + 75);
        }
        if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock.getElapsedTime().asSeconds() < 0.5) {
            m_fire.move(sf::Vector2f(15, 0));
        }
        if (fireClock2.getElapsedTime().asSeconds() > 0.15 && fireClock2.getElapsedTime().asSeconds() < 0.55) {
            m_fire2.move(sf::Vector2f(15,0));
        }
        if (fireClock.getElapsedTime().asSeconds() > 0.5) {
            fireClock.restart();
        }
        if (fireClock2.getElapsedTime().asSeconds() > 0.55) {
            fireClock2.restart();
        }
        if(animatorClock.getElapsedTime().asSeconds() < 0.1) {
            m_player.load("dragon.png",0,192,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.1 && animatorClock.getElapsedTime().asSeconds() < 0.2) {
            m_player.load("dragon.png",96,192,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.2 && animatorClock.getElapsedTime().asSeconds() < 0.3) {
            m_player.load("dragon.png",192,192,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.3 && animatorClock.getElapsedTime().asSeconds() < 0.4) {
            m_player.load("dragon.png",288,192,96,96);
        }
        if(animatorClock.getElapsedTime().asSeconds() > 0.4) {
            animatorClock.restart();
        }
        if(positionBack.x <= 0 && positionBack.x >= -1500){
            m_background.move(sf::Vector2f(-1,0));
            m_backgroundFiller.move(sf::Vector2f(-1,0));
        }
        if(positionBack.x == -1500){
            m_background.setPosition(1500,0);
        }
        if(positionBack.x >= 0 || positionBackFiller.x <= 1500){
            m_backgroundFiller.move(sf::Vector2f(-1,0));
            m_background.move(sf::Vector2f(-1,0));
        }
        if(positionBackFiller.x == -1500){
            m_backgroundFiller.setPosition(1500,0);
        }
        if(snake1Position.x <= 1500 && snake2Position.x <= 1500){
            m_Snake1.move(sf::Vector2f(-1.0,0));
            m_Snake2.move(sf::Vector2f(-1.0,0));
        }
        if(snake1Position.x == -50 && snake2Position.x == -50){
            int pos1 = rand() % 250 + 50;
            int pos2 = rand() % 330 + 355;
            m_Snake1.setPosition(1500,pos1);
            m_Snake2.setPosition(1500,pos2);
        }
        if(position.y < 0){
            m_speed = 0;
            m_player.setPosition(position.x, position.y + 4);
        }
        if(position.y > 575){
            m_speed = 0;
            m_player.setPosition(position.x, position.y - 4);
        }
        m_speed = 300.0f;

        if(m_fire.getGlobalBounds().intersects(m_Snake1.getGlobalBounds()) || m_fire2.getGlobalBounds().intersects(m_Snake1.getGlobalBounds()) ){
            int pos1 = rand() % 250 + 50;
            m_Snake1.setPosition(1500,pos1);
        }
        if(m_fire.getGlobalBounds().intersects(m_Snake2.getGlobalBounds()) || m_fire2.getGlobalBounds().intersects(m_Snake2.getGlobalBounds()) ){
            int pos2 = rand() % 330 + 355;
            m_Snake2.setPosition(1500,pos2);
        }
        if(m_player.getGlobalBounds().intersects(m_Snake1.getGlobalBounds()) || m_player.getGlobalBounds().intersects(m_Snake2.getGlobalBounds()) ){
           m_window.close();
        }



        //std::cout << position.y<<  std::endl;
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
    //if(key == sf::Keyboard::Left)
      //  m_left = isDown;
    //if(key == sf::Keyboard::Right)
     //   m_right = isDown;
    if(key == sf::Keyboard::Up)
        m_up = isDown;
    if(key == sf::Keyboard::Down)
        m_down = isDown;
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
    m_background.draw(m_window);
    m_backgroundFiller.draw(m_window);
    m_player.draw(m_window);
    m_fire.draw(m_window);
    m_fire2.draw(m_window);
    m_Snake1.draw(m_window);
    m_Snake2.draw(m_window);
    m_window.display();
}