#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <cmath>

#include "AnimatedSprite.h"

class Enemy : public AnimatedSprite {
public:
    void movingRight();
    void movingLeft();
    bool moving() {}
    void setFrames() = 0;
    void step(float &time);
    void mirror();
    void control(float &time);
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
protected:
    double distance_x_, sum_of_distance_x_;
    int direction_;
};

void Enemy::movingLeft(){
    moving_left_ = true;
    moving_right_ = false;
}

void Enemy::movingRight(){
    moving_left_ = false;
    moving_right_ = true;
}

void Enemy::control(float &time){
    distance_x_ = direction_ * vel_x_ * time;
    sum_of_distance_x_ += distance_x_;
    if(fabs(sum_of_distance_x_) < 200){
        move(distance_x_, 0);
    }else{
        sum_of_distance_x_ = 0;
        direction_ = -direction_;
    }
}

void Enemy::mirror(){
    sf::IntRect temp = animated_walking_[0];
    float origin_x = temp.width;
    float origin_y = temp.height;
    setOrigin(origin_x / 2, origin_y / 2);
    if (direction_ > 0) {
        setScale(1, 1);
    }
    if (direction_ < 0) {
        setScale(-1, 1);
    }
}

void Enemy::step(float &time){
    sec_walking_ += time;
    setFrames();
    mirror();
    if (sec_walking_ >= 1.0 / frames_) {
        setTextureRect(animated_walking_[current_frame_index_]);
        if (current_frame_index_ >= animated_walking_.size() - 1) {
            current_frame_index_ = 0;
        } else {
            current_frame_index_++;
        }
        sec_walking_ = 0;
    }
}

#endif // ENEMY_H
