//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject();
    virtual bool load(const std::string& filename, int para1, int para2, int para3, int para4);

    virtual void draw(sf::RenderWindow& window);

    virtual void update(float deltaT) {}

    virtual void setPosition(float x, float y);

    virtual void move(sf::Vector2f);

    virtual sf::Vector2f getPosition() const;

    virtual float getHeight() const;

    virtual float getWidth() const;

    virtual void setScale(float scale);

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    std::string m_filename;
    bool m_valid = false;

};


