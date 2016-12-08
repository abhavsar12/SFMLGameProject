//
// Created by bswenson3 on 11/9/16.
//

#include "GameObject.h"

GameObject::GameObject() {

}

bool GameObject::load(const std::string& filename, int para1, int para2, int para3, int para4) {
    if(m_texture.loadFromFile(filename)) {
        m_filename = filename;
        m_sprite.setTexture(m_texture);
        m_sprite.setTextureRect(sf::IntRect(para1,para2,para3,para4)); //Gives a certain Sprite
        m_valid = true;
        return true;
    }
    return false;
}

void GameObject::draw(sf::RenderWindow& window) {
    if(m_valid)
        window.draw(m_sprite);
}

void GameObject::move(sf::Vector2f loc) {
    if(m_valid)
        m_sprite.move(loc);
}

void GameObject::setPosition(float x, float y) {
    if(m_valid)
        m_sprite.setPosition(x, y);
}

sf::Vector2f GameObject::getPosition() const {
    if(m_valid)
        return m_sprite.getPosition();
    else
        return sf::Vector2f(0, 0);
}

float GameObject::getHeight() const {
    return m_sprite.getLocalBounds().height;
}

float GameObject::getWidth() const {
    return m_sprite.getLocalBounds().width;
}

void GameObject::setScale(float scale) {
    if(m_valid)
        m_sprite.setScale(scale, scale);
}