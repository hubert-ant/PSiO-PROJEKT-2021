#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "AnimatedSprite.h"
#include "Enemy.h"

class Player;

class Bullet : public AnimatedSprite {
public:
    void movingRight();
    void movingLeft();
    bool moving() {}
    void setFrames() = 0;
    void mirror() = 0;
    virtual void step(float &time);
    virtual void fired(float &time) = 0;
    virtual void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &vec, Player &player, float time) = 0;
    void control(float &time) {}
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) {}
};

void Bullet::movingLeft() {
    moving_left_ = true;
}

void Bullet::movingRight() {
    moving_right_ = true;
}

void Bullet::step(float &time){
    if (sec_walking_ == 0) {
        setTextureRect(animated_walking_[current_frame_index_]);
        if (current_frame_index_ >= animated_walking_.size() - 1) {
            current_frame_index_ = 0;
        } else {
            current_frame_index_++;
        }
    }
    sec_walking_ += time;
    if (sec_walking_ >= 1.0 / frames_) {
        sec_walking_ = 0;
    }
}

#endif // BULLET_H
