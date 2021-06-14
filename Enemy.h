#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "AnimatedSprite.h"

class Enemy : public AnimatedSprite {
public:
    Enemy(double x, double y, const std::string &filename);
    void movingRight() {}
    void movingLeft() {}
    bool moving() {}
    void setFrames() {}
    void step(float& time) {}
    void mirror() {}
};

Enemy::Enemy(double x, double y, const std::string &filename) {
    x_ = x;
    y_ = y;
    filename_ = filename;
}

#endif // ENEMY_H
