//
// Created by bswenson3 on 11/9/16.
//

#include <string.h>
#include <netdb.h>
#include "Game.h"

Game::Game() :
    m_window(sf::VideoMode(2000, 1000), "NeverWing")


{
    //load the player
    m_player.load("dragon.png",288,192,96,96);
    m_player2.load("dragon.png",288,192,96,96);
    m_titleSlide.load("Title.png",0,0,2000,1000);
    m_titleSlide.load("Title.png",0,0,2000,1000);
    m_Story1.load("Story1.png",0,0,3000,1500);
    m_Story2.load("Story2.png",0,0,2000,1000);
    m_fire.load("fire.png",0,256,64,64);
    m_fire2.load("fire.png",0,256,64,64);
    m_fire3.load("fire.png",0,256,64,64);
    m_fire4.load("fire.png",0,256,64,64);
    m_Snake1.load("Snakes.png",0,0,200,150);
    m_Snake2.load("Snakes.png",0,0,200,150);
    m_Snake3.load("Snakes.png",0,0,200,150);
    m_Snake4.load("Snakes.png",0,0,200,150);
    m_background.load("background.png",0,0,2000,1000);
    m_backgroundFiller.load("background.png",0,0,2000,1000);
    m_endGame.load("GameOver.png",0,0,2000,1000);


    line.setSize(sf::Vector2f(2000,25));
    line.setPosition(0,500);


    m_backgroundFiller.setPosition(2000,0);


    m_player.setPosition(35,268);
    m_player2.setPosition(35,750);
    m_Snake1.setPosition(2000,0);
    m_Snake2.setPosition(2000,275);
    m_Snake3.setPosition(2000,0);
    m_Snake4.setPosition(2000,275);




    //size him.  trial and error to get correct values
    m_player.setScale(2.0f);
    m_player2.setScale(2.0f);
    m_fire.setScale(2.0f);
    m_fire2.setScale(2.0f);
    m_fire3.setScale(2.0f);
    m_fire4.setScale(2.0f);
    m_Snake1.setScale(0.9f);
    m_Snake2.setScale(0.9f);
    m_Snake3.setScale(0.9f);
    m_Snake4.setScale(0.9f);




}

void Game::run() {
    sf::Clock clock;
    sf::Clock press;
    sf::Clock animatorClock;
    sf::Clock animatorClock2;
    sf::Clock fireClock;
    sf::Clock fireClock2;
    state = 0;
    bool restart = false;
    score1 = 0;
    highScore = 0;
    sf::Font font;
    font.loadFromFile("Apple Chancery.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setColor(sf::Color::Black);

    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setColor(sf::Color::Black);
    text2.setPosition(1750,435+500);

    text3.setFont(font);
    text3.setCharacterSize(200);
    text3.setColor(sf::Color::Black);
    text3.setPosition(1000,500);

    highscoretext.setFont(font);
    highscoretext.setCharacterSize(50);
    highscoretext.setColor(sf::Color::Black);
    highscoretext.setPosition(1150,350);


    //sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//    sf::TcpSocket socket;
//    char connectionType, mode;
//    char buffer[2000];
//    std::size_t received;
//    std::string text1 = "Connected to:";
//    const std::string IPADDRESS("128.61.16.74");
//    const unsigned short PORT = 2000;
//
//
//
//    std::cout << "Enter (s) for server, Enter (c) for client" << std::endl;
//    std::cin >> connectionType;
//    if(connectionType == 's'){
//        sf::TcpListener listener;
//        listener.listen(2000);
//        listener.accept(socket);
//        text1 += "server";
//        mode = 's';
//    }
//    else if(connectionType == 'c'){
//        socket.connect("128.61.16.74",2000);        // This needs to be changed later!!!!!!
//        text1 += "client";
//        mode = 'r';
//
//    }
//
//    socket.send(text1.c_str(),text1.length() + 1);
//    socket.receive(buffer, sizeof(buffer), received);
//    std::cout << buffer << std::endl;
//
//    bool done = false;
//
//    while(!done){
//        if(mode == 's'){
//            std::getline(std::cin,text1);
//            socket.send(text1.c_str(),text1.length() + 1);
//            mode = 'r';
//        }
//        else if(mode == 'r'){
//            socket.receive(buffer, sizeof(buffer), received);
//            if(received > 0){
//                std::cout << "Received: " << buffer << std::endl;
//                mode = 's';
//            }
//        }
//    }
//
//    //system("pause");


    while(m_window.isOpen()) {
        if(state == 0){
            sf::Time deltaT = clock.restart();
            processEvents();
            update(deltaT);
            renderTitle();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                restart = true;
                server = false;
                setupClient();
                if (press.getElapsedTime().asSeconds() > 0) {
                    state += 1;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                restart = true;
                server = true;
                setupServer();
                if (press.getElapsedTime().asSeconds() > 0) {
                    state += 1;
                }
            }
        }

        if(state == 1){
            sf::Time deltaT = clock.restart();
            if (restart == true) {
                press.restart();
            }
            restart = false;
            processEvents();
            update(deltaT);
            renderStory1();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                restart = true;
                if (press.getElapsedTime().asMilliseconds() > 100 ) {
                    state += 1;
                }
            }
        }

        if(state == 2){
            sf::Time deltaT = clock.restart();
            if (restart == true) {
                press.restart();
            }
            restart = false;
            processEvents();
            update(deltaT);
            renderStory2();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                restart = true;
                if (press.getElapsedTime().asMilliseconds() > 100) {
                    state += 1;
                }
            }
        }
        if(state == 3) {
            text.setPosition(1750,435);
            sf::Vector2f position = m_player.getPosition();
            sf::Vector2f position2 = m_player2.getPosition();
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
            if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock.getElapsedTime().asSeconds() < 0.9) {
                m_fire.move(sf::Vector2f(35, 0));
            }
            if (fireClock2.getElapsedTime().asSeconds() > 0.15 && fireClock2.getElapsedTime().asSeconds() < 0.95) {
                m_fire2.move(sf::Vector2f(35, 0));
            }
            if (fireClock.getElapsedTime().asSeconds() > 0.5) {
                fireClock.restart();
            }
            if (fireClock2.getElapsedTime().asSeconds() > 0.55) {
                fireClock2.restart();
            }
            if (animatorClock.getElapsedTime().asSeconds() < 0.1) {
                m_player.load("dragon.png", 0, 192, 96, 96);
            }
            if (animatorClock.getElapsedTime().asSeconds() > 0.1 && animatorClock.getElapsedTime().asSeconds() < 0.2) {
                m_player.load("dragon.png", 96, 192, 96, 96);
            }
            if (animatorClock.getElapsedTime().asSeconds() > 0.2 && animatorClock.getElapsedTime().asSeconds() < 0.3) {
                m_player.load("dragon.png", 192, 192, 96, 96);
            }
            if (animatorClock.getElapsedTime().asSeconds() > 0.3 && animatorClock.getElapsedTime().asSeconds() < 0.4) {
                m_player.load("dragon.png", 288, 192, 96, 96);
            }
            if (animatorClock.getElapsedTime().asSeconds() > 0.4) {
                animatorClock.restart();
            }
            if (positionBack.x <= 0 && positionBack.x >= -2000) {
                m_background.move(sf::Vector2f(-4, 0));
                m_backgroundFiller.move(sf::Vector2f(-4, 0));
            }
            if (positionBack.x == -2000) {
                m_background.setPosition(2000, 0);
            }
            if (positionBack.x >= 0 || positionBackFiller.x <= 2000) {
                m_backgroundFiller.move(sf::Vector2f(-4, 0));
                m_background.move(sf::Vector2f(-4, 0));
            }
            if (positionBackFiller.x == -2000) {
                m_backgroundFiller.setPosition(2000, 0);
            }
            if (snake1Position.x <= 2000 && snake2Position.x <= 2000) {
                m_Snake1.move(sf::Vector2f(-3.0, 0));
                m_Snake2.move(sf::Vector2f(-3.0, 0));
            }
            if (snake1Position.x == -100) {
                int pos1 = rand() % 300 + 0;
                m_Snake1.setPosition(2000, pos1);
            }
            if(snake2Position.x == -100){
                int pos2 = rand() % 300 + 0;
                m_Snake2.setPosition(2000, pos2);
            }
            if (position.y < 0) {
                m_speed = 0;
                m_player.setPosition(position.x, position.y + 4);
            }
            if (position.y > 300) {
                m_speed = 0;
                m_player.setPosition(position.x, position.y - 4);
            }
            m_speed = 300.0f;

            if (m_fire.getGlobalBounds().intersects(m_Snake1.getGlobalBounds()) || m_fire2.getGlobalBounds().intersects(m_Snake1.getGlobalBounds())) {
                score1 += 1;
                int pos1 = rand() % 300 + 0;
                m_Snake1.setPosition(2000, pos1);
                m_fire.setPosition(position.x,position.y);
                m_fire2.setPosition(position.x,position.y);
                std::string s = std::to_string(score1);
                std::string score1 = "Score:" + s;
                text.setString(score1);

            }
            if (m_fire.getGlobalBounds().intersects(m_Snake2.getGlobalBounds()) || m_fire2.getGlobalBounds().intersects(m_Snake2.getGlobalBounds())) {
                score1 += 1;
                int pos2 = rand() % 300 + 0;
                m_Snake2.setPosition(2000, pos2);
                m_fire.setPosition(position.x,position.y);
                m_fire2.setPosition(position.x,position.y);
                std::string s = std::to_string(score1);
                std::string score = "Score: " + s;
                text.setString(score);
            }
            if (m_player.getGlobalBounds().intersects(m_Snake1.getGlobalBounds()) || m_player.getGlobalBounds().intersects(m_Snake2.getGlobalBounds())) {
                m_Snake1.setPosition(2000,268);
                m_Snake2.setPosition(2000,600);
                state += 1;
            }
            //---------------------------------------------------------------------------------------------------------------------------------------------

            if (animatorClock2.getElapsedTime().asSeconds() < 0.1) {
                m_player2.load("dragon.png", 0, 192, 96, 96);
            }
            if (animatorClock2.getElapsedTime().asSeconds() > 0.1 && animatorClock2.getElapsedTime().asSeconds() < 0.2) {
                m_player2.load("dragon.png", 96, 192, 96, 96);
            }
            if (animatorClock2.getElapsedTime().asSeconds() > 0.2 && animatorClock2.getElapsedTime().asSeconds() < 0.3) {
                m_player2.load("dragon.png", 192, 192, 96, 96);
            }
            if (animatorClock2.getElapsedTime().asSeconds() > 0.3 && animatorClock2.getElapsedTime().asSeconds() < 0.4) {
                m_player2.load("dragon.png", 288, 192, 96, 96);
            }
            if (animatorClock2.getElapsedTime().asSeconds() > 0.4) {
                animatorClock2.restart();
            }

            if (fireClock.getElapsedTime().asSeconds() < 0.1) {
                m_fire3.setPosition(position2.x + 150, position2.y + 75);
            }
            if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock2.getElapsedTime().asSeconds() < 0.15) {
                m_fire4.setPosition(position2.x + 150, position2.y + 75);
            }
            if (fireClock.getElapsedTime().asSeconds() > 0.1 && fireClock.getElapsedTime().asSeconds() < 0.9) {
                m_fire3.move(sf::Vector2f(35, 0));
            }
            if (fireClock2.getElapsedTime().asSeconds() > 0.15 && fireClock2.getElapsedTime().asSeconds() < 0.95) {
                m_fire4.move(sf::Vector2f(35, 0));
            }
            if (fireClock.getElapsedTime().asSeconds() > 0.5) {
                fireClock.restart();
            }
            if (fireClock2.getElapsedTime().asSeconds() > 0.55) {
                fireClock2.restart();
            }

            if (position2.y < 506) {
                m_speed = 0;
                m_player2.setPosition(position.x, position.y + 4);
            }
            if (position2.y > 840) {
                m_speed = 0;
                m_player2.setPosition(position.x, position.y - 4);
            }

            gameOver = false;

            //std::cout << position2.y<<  std::endl;
            sf::Time deltaT = clock.restart();
            processEvents();
            update(deltaT);
            render();
            //usleep(10000); // To prevent crashing
        }

        if(state == 4) {
            sf::Time deltaT = clock.restart();
            text.setPosition(1150,300);
            gameOver = true;

            if(score1 > highScore){
                highScore = score1;
                std::string s = std::to_string(score1);
                std::string score = "Score: " + s;
                text.setString(score);

                std::string h = std::to_string(highScore);
                std::string highscore = "High Score: " + s;
                highscoretext.setString(highscore);

            }
            if(score1 < highScore){
                std::string s = std::to_string(score1);
                std::string score = "Score: " + s;
                text.setString(score);

                std::string h = std::to_string(highScore);
                std::string highscore = "High Score: " + h;
                highscoretext.setString(highscore);
            }
            if (restart == true) {
                press.restart();
            }
            restart = false;
            processEvents();
            update(deltaT);
            renderEndGame();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                restart = true;
                if (press.getElapsedTime().asMilliseconds() > 100) {
                    state -= 1;
                    score1 = 0;
                    score2 = 0;
                }
            }

        } if (state == 5) {
            sf::Time deltaT = clock.restart();
            if (score1 > highScore) {
                highScore = score1;
            }
            text.setPosition(1150,300);
            std::string s = std::to_string(score1);
            std::string score = "Score: " + s;
            text.setString(score);

            std::string h = std::to_string(highScore);
            std::string highscore = "High Score: " + h;
            highscoretext.setString(highscore);

            if (restart == true) {
                press.restart();
            }
            restart = false;
            processEvents();
            update(deltaT);
            renderWinGame();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                restart = true;
                if (press.getElapsedTime().asMilliseconds() > 0) {
                    state -= 2;
                    score1 = 0;
                    score2 = 0;
                }
            }
        }

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
                close(newsockfd);
                close(sockfd);
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
    if(m_up) {
        movement.y -= m_speed;
    }
    if(m_down)
        movement.y += m_speed;
    if(m_left)
        movement.x -= m_speed;
    if(m_right)
        movement.x += m_speed;


    m_player.move(movement * deltaT.asSeconds());

}

void Game::renderTitle() {
    m_window.clear();
    m_titleSlide.draw(m_window);
    m_window.display();

}

void Game::renderStory1(){
    m_window.clear();
    m_Story1.draw(m_window);
    m_window.display();

}

void Game::renderStory2() {
    m_window.clear();
    m_Story2.draw(m_window);
    m_window.display();

}

void Game::render() {

    // Send dragon data in a 4 byte int, last int is an opcode
    // Dragon y value is set to opcode 0
    if (sending) {
        p2Win = false;
        sf::Vector2f pos;
        short val;
        short send;
        if (renderCounter == 0) {
            pos = m_player.getPosition();
            val = (short) pos.y;
            send = val | 0x0000;
            /*if (server) {

            } else {
                err = write(sockfd, &send, 4);
            }*/
        }

        if (renderCounter == 1) {
            pos = m_Snake1.getPosition();
            val = (short) pos.x;
            send = val | 0x1000;
            /*if (server) {
                err = write(newsockfd, &send, 4);
            } else {
                err = write(sockfd, &send, 4);
            }*/
        }

        if (renderCounter == 2) {
            pos = m_Snake1.getPosition();
            val = (short) pos.y;
            send = val | 0x2000;
            /*if (server) {
                err = write(newsockfd, &send, 4);
            } else {
                err = write(sockfd, &send, 4);
            }*/
        }

        if (renderCounter == 3) {
            pos = m_Snake2.getPosition();
            val = (short) pos.x;
            send = val | 0x3000;
            /*if (server) {
                err = write(newsockfd, &send, 4);
            } else {
                err = write(sockfd, &send, 4);
            }*/
        }

        if (renderCounter == 4) {
            pos = m_Snake2.getPosition();
            val = (short) pos.y;
            send = val | 0x4000;
            /*if (server) {
                err = write(newsockfd, &send, 4);
            } else {
                err = write(sockfd, &send, 4);
            }*/
        }

        if (renderCounter == 5) {
            val = (short) score1;
            send = val | 0x5000;
            /*if (server) {
                err = write(newsockfd, &send, 4);
            } else {
                err = write(sockfd, &send, 4);
            }*/
        }

        std::string str = std::to_string(send);
        socket.send(str.c_str(), str.length() + 1);
        sending = false;
    } else {
        short buf = 600;
        sf::Socket::Status stat = socket.receive(buffer, sizeof(buffer), received);
        if (stat == sf::Socket::Status::Done) {
            /*if (server) {
                err = read(newsockfd, &buf, 4);
            } else {
                err = read(sockfd, &buf, 4);
            }*/

            //std::cout << buf2 << std::endl;
            //int out = buf;
            short out = std::atoi(buffer);
            std::cout << buf << std::endl;
            short opcode = out & 0xF000;
            opcode = opcode >> 12;
            int value = out & 0x0FFF;
            std::cout << opcode << std::endl;
            if (value < 3000) {

                if (opcode == 0x0) {
                    dragonposition = value;
                    m_player2.setPosition(35, dragonposition + 550);
                }

                if (opcode == 0x1) {
                    snake1xposition = value;
                    m_Snake3.setPosition((float) snake1xposition, m_Snake3.getPosition().y + 550);
                }

                if (opcode == 0x2) {
                    snake1yposition = value;
                    m_Snake3.setPosition(m_Snake3.getPosition().x, (float) snake1yposition + 550);
                }

                if (opcode == 0x3) {
                    snake2xposition = value;
                    m_Snake4.setPosition((float) snake2xposition, m_Snake4.getPosition().y + 550);
                }

                if (opcode == 0x4) {
                    snake2yposition = value;
                    m_Snake4.setPosition(m_Snake4.getPosition().x, (float) snake2yposition + 550);
                }

                if (opcode == 0x5) {
                    score2 = value;
                    text2.setString("Score: " + std::to_string(score2));
                }

                if (opcode == 0x6) {
                    text3.setString("You Won!");
                    if (score1 > highScore) {
                        highScore = score1;
                    }
                    p2Win = true;
                }
            }

            if (renderCounter < 5) {
                renderCounter++;
            } else {
                renderCounter = 0;
            }
        }
        sending = true;
    }

    m_window.clear();
    m_background.draw(m_window);
    m_backgroundFiller.draw(m_window);
    m_player.draw(m_window);
    m_player2.draw(m_window);
    m_fire.draw(m_window);
    m_fire2.draw(m_window);
    m_fire3.draw(m_window);
    m_fire4.draw(m_window);
    m_Snake1.draw(m_window);
    m_Snake2.draw(m_window);
    m_Snake3.draw(m_window);
    m_Snake4.draw(m_window);
    if (score1 > 0) {
        m_window.draw(text);
    }
    if (score2 > 0) {
        m_window.draw(text2);
    }
    if (p2Win) {
        state = 5;
    }
    m_window.draw(line);
    m_window.display();
}

void Game::renderEndGame(){
    short send = 1 | 0x6000;
    std::string str = std::to_string(send);
    socket.send(str.c_str(),str.length() + 1);

    m_window.clear();
    m_endGame.draw(m_window);
    m_window.draw(text);
    m_window.draw(highscoretext);
    m_window.display();
}

void Game::renderWinGame() {
    m_window.clear();
    m_endGame.draw(m_window);
    m_window.draw(text);
    m_window.draw(highscoretext);
    m_window.draw(text3);
    m_window.display();
}

void Game::setupServer() {
    sf::TcpListener listener;
    listener.listen(2001);
    listener.accept(socket);
    /*
    int portno;
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /*if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cout << "Error sockfd" << std::endl;
        close(sockfd);
    }
    //error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 2002;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) {
        std::cout << "Error binding" << std::endl;
        //error("ERROR on binding");
        close(sockfd);
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0) {
        std::cout << "Error" << std::endl;
        close(newsockfd);
        close(sockfd);
    }
    */
}

void Game::setupClient() {
    socket.connect("128.61.17.46",2001);
    /*
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = 2002;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cout << "Socket error" << std::endl;
        close(sockfd);
        //error("ERROR opening socket");
    }
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        std::cout << "Error connecting" << std::endl;
        close(sockfd);
    }

    */
        //error("ERROR connecting");
    //printf("Please enter the message: ");
    //bzero(buffer,256);
    //fgets(buffer,255,stdin);
    //err = write(sockfd,buffer,strlen(buffer));
    /*if (err < 0)
        error("ERROR writing to socket");*/
};

