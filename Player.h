#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <string>
#include <vector>

#include "AnimatedSprite.h"
#include "Bullet.h"

class Player : public AnimatedSprite {
public:
    Player(double x, double y, double vel_x, double vel_y, const std::string &filename);
    void control(float& time, std::vector<std::unique_ptr<AnimatedSprite>> &vec);
    void shoot(std::vector<std::unique_ptr<Bullet>> &vec);
    void movingLeft();
    void movingRight();
    void step(float &time);
    void setFrames();
    bool moving();
    void mirror();
    void animate(float &time);
    bool verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object);
    bool horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object);
protected:
    double acceleration_, distance_jump_, next_pos_x_, next_pos_y_;
    bool horizontal_collision_, vertical_collision_, moving_up_, moving_down_;
};

Player::Player(double x, double y, double vel_x, double vel_y, const std::string &filename) {
    x_ = x;
    y_ = y;
    vel_x_ = vel_x;
    vel_y_ = vel_y;
    filename_ = filename;
    moving_right_ = true;
    frames_ = 3;
    current_frame_index_ = 0;
    sec_ = 0;
    acceleration_ = 100;
    moving_up_ = false;
    moving_down_ = false;
}

void Player::movingLeft() {
    moving_left_ = true;
    moving_right_ = false;
}

void Player::movingRight() {
    moving_left_ = false;
    moving_right_ = true;
}

void Player::control(float &time, std::vector<std::unique_ptr<AnimatedSprite>> &vec) {
    horizontal_collision_ = false;
    vertical_collision_ = false;
//    vel_y_ += acceleration_ * time;
    next_pos_y_ = vel_y_ * time;
    for (const auto & rec : vec) {
        if (verticalCollison(next_pos_y_, rec)) {
            vertical_collision_ = true;
        }
        if (horizontalCollison(next_pos_x_, rec)) {
            horizontal_collision_ = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        next_pos_x_ = -vel_x_ * time;
        this->movingLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        next_pos_x_ = vel_x_ * time;
        this->movingRight();
    } else {
        next_pos_x_ = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        moving_up_ = true;
    }
    if (!moving_up_) {
        if (!vertical_collision_) {
            move(0, next_pos_y_);
        }
    } else {
        move(0, -next_pos_y_);
        distance_jump_ += next_pos_y_;
        if (vertical_collision_ || distance_jump_ > 150) {
            moving_up_ = false;
            distance_jump_ = 0;
        }
    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//        next_pos_y_ = -next_pos_y_;
//    }
//    if(!vertical_collision_ || moving_up_){
//        move(0, next_pos_y_);
//    }else{
//        next_pos_y_ = 0;
//    }
    if (!horizontal_collision_) {
        move(next_pos_x_, 0);
    }
}

bool Player::verticalCollison(float next_pos_y, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().top + getGlobalBounds().height + next_pos_y >= object->getGlobalBounds().top &&
        getGlobalBounds().top + next_pos_y <= object->getGlobalBounds().top + object->getGlobalBounds().height &&
        !(getGlobalBounds().left >= object->getGlobalBounds().left + object->getGlobalBounds().width ||
          getGlobalBounds().left + getGlobalBounds().width <= object->getGlobalBounds().left)) {
        return true;
    }
    return false;
}

bool Player::horizontalCollison(float next_pos_x, const std::unique_ptr<AnimatedSprite> &object) {
    if (getGlobalBounds().left + next_pos_x <= object->getGlobalBounds().left + object->getGlobalBounds().width &&
        getGlobalBounds().left + getGlobalBounds().width + next_pos_x >= object->getGlobalBounds().left &&
        !(getGlobalBounds().top >= object->getGlobalBounds().height + object->getGlobalBounds().top ||
          getGlobalBounds().top + getGlobalBounds().height <= object->getGlobalBounds().top)) {
        return true;
    }
    return false;
}

void Player::shoot(std::vector<std::unique_ptr<Bullet>> &vec) {
    float x, y;
    if (this->moving_right_) {
        x = this->getGlobalBounds().left + this->getGlobalBounds().width;
    } else {
        x = this->getGlobalBounds().left;
    }
    y = this->getGlobalBounds().top + (this->getGlobalBounds().height / 2);
    auto bullet = std::make_unique<Bullet>(x, y, "bullet");
    if (this->moving_right_) {
        bullet->movingRight();
    }
    if (this->moving_left_) {
        bullet->movingLeft();
    }
    bullet->setPos();
    bullet->setText();
    bullet->setFrames();
    bullet->mirror();
    vec.emplace_back(std::move(bullet));
}

void Player::setFrames() {
    this->addAnimationFrame(sf::IntRect(0, 0, 567, 556), animated_character_);
    this->addAnimationFrame(sf::IntRect(567, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1134, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(1701, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(2268, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(2835, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(3402, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(3969, 0, 567, 556), animated_walking_);
    this->addAnimationFrame(sf::IntRect(4536, 0, 567, 556), animated_walking_);
}

void Player::mirror() {
    sf::IntRect temp = animated_character_[0];
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

bool Player::moving() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return true;
    }
    return false;
}

void Player::step(float &time) {
    sec_ += time;
    setFrames();
    mirror();
    if (!moving()) {
        setTextureRect(animated_character_[0]);
    } else {
        if (sec_ >= 1.0 / frames_) {
            setTextureRect(animated_walking_[current_frame_index_]);
            if (current_frame_index_ >= animated_walking_.size() - 1) {
                current_frame_index_ = 0;
            } else {
                current_frame_index_++;
            }
            sec_ = 0;
        }
    }
}

#endif // PLAYER_H
