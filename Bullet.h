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
    void setFrames();
    void mirror();
    void step(float &time);
    Bullet(double x, double y, const std::string &filename);
    void fired(float &time);
    void collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
};

Bullet::Bullet(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
    vel_x_ = 200;
    frames_ = 5;
    current_frame_index_ = 0;
    sec_ = 0;
}

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
        setScale(0.1, 0.1);
    }
    if (moving_left_ == true) {
        setScale(-0.1, 0.1);
    }
}

void Bullet::setFrames() {
    this->addAnimationFrame(sf::IntRect(0, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(172, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(344, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(516, 0, 172, 139), animated_walking_);
    this->addAnimationFrame(sf::IntRect(688, 0, 172, 139), animated_walking_);
}

void Bullet::step(float &time) {
    if (sec_ == 0) {
        setTextureRect(animated_walking_[current_frame_index_]);
        if (current_frame_index_ >= animated_walking_.size() - 1) {
            current_frame_index_ = 0;
        } else {
            current_frame_index_++;
        }
    }
    sec_ += time;
    if (sec_ >= 1.0 / frames_) {
        sec_ = 0;
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

void Bullet::collision(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<AnimatedSprite>> &objects) {
    for (auto bullet = bullets.begin(); bullet < bullets.end(); ++bullet) {
        for (auto object = objects.begin(); object < objects.end(); object++) {
            auto enemy = dynamic_cast<Enemy*>(object->get());
            if ((*bullet)->getGlobalBounds().intersects((*object)->getGlobalBounds())) {
                if (enemy != nullptr) {
                    objects.erase(object);
                }
                bullets.erase(bullet);
                break;
            }
        }
    }
}

#endif // BULLET_H
