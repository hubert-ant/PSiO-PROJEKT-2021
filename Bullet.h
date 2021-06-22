#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "AnimatedSprite.h"
#include "Enemy.h"

class Bullet : public AnimatedSprite {
public:
    void movingRight();
    void movingLeft();
    bool moving() {}
    void setFrames() = 0;
    void mirror();
    void step(float &time) = 0;
    void fired(float &time);
    virtual void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &vec) = 0;
    void control(float &time) {}
};

void Bullet::movingLeft() {
    moving_left_ = true;
}

void Bullet::movingRight() {
    moving_right_ = true;
}

void Bullet::mirror() {
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (moving_right_ == true) {
        setScale(0.08, 0.08);
    }
    if (moving_left_ == true) {
        setScale(-0.08, 0.08);
    }
}

void Bullet::fired(float &time) {
    float distance = vel_x_ * time;
    if (moving_left_) {
        move(-distance, 0);
    }
    if (moving_right_) {
        move(distance, 0);
    }
}

#endif // BULLET_H
