#ifndef BULLETENEMYGOBLIN_H
#define BULLETENEMYGOBLIN_H

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"
#include "Bullet.h"

class Bulletenemygoblin : public Bullet{
public:
    Bulletenemygoblin (double x, double y, const std::string &filename);
    void setFrames();
    void mirror();
    void fired(float &time){}
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects, Player &player){}
};

Bulletenemygoblin ::Bulletenemygoblin (double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 10;
    current_frame_index_ = 0;
    sec_walking_ = 0;
}

void Bulletenemygoblin::mirror() {
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (moving_right_ == true) {
        setScale(-1, 1);
    }
    if (moving_left_ == true) {
        setScale(-1, 1);
    }
}

void Bulletenemygoblin::setFrames(){
    this->addAnimationFrame(sf::IntRect(0, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(100, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(200, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(300, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(400, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(500, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(600, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(700, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(800, 0, 100, 100), animated_walking_);
    this->addAnimationFrame(sf::IntRect(900, 0, 100, 100), animated_walking_);
}

#endif // BULLETENEMYGOBLIN_H
