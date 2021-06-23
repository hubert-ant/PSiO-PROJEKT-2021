#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <cmath>

#include "AnimatedSprite.h"


class Bullet;

class Enemy : public AnimatedSprite  {
public:
    void movingRight();
    void movingLeft();
    bool moving();
    void setFrames() = 0;
    void step(float &time) = 0;
    void mirror();
    void control(float &time);
    void randomDirection();
    static void setEnemies(std::vector<std::unique_ptr<AnimatedSprite>> &objects);
    void shoot(std::vector<std::unique_ptr<Bullet>> &bullets) = 0;
protected:
    double distance_x_, time_of_staying_, sum_of_distance_x = 0;
};

void Enemy::movingLeft(){
    moving_left_ = true;
    moving_right_ = false;
}

void Enemy::movingRight(){
    moving_left_ = false;
    moving_right_ = true;
}

bool Enemy::moving(){
    if(timer_ >= 0){
        return false;
    }
    return true;
}

void Enemy::control(float &time){
    distance_x_ = direction_ * vel_x_ * time;
    time_of_staying_ += time;
    sum_of_distance_x += distance_x_;
    if(time_of_staying_ >= 2){
        timer_ = time_of_staying_;
        time_of_staying_ = 0;
    }
    if(!moving()){
        time_of_staying_ = 0;
        timer_ -= time;
    }else{
        if(getPosition().x > x_ - 100 && getPosition().x < x_ + 100){
            move(distance_x_, 0);
        }else{
            direction_ = -direction_;
            move(-distance_x_, 0);
        }
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

#endif // ENEMY_H
